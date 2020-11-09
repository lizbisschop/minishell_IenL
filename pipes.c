/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 18:18:33 by iboeters      #+#    #+#                 */
/*   Updated: 2020/11/09 18:18:34 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_and_child(t_mini *mini, int *pid, int i)
{
	dup2(mini->fd_out, STDOUT_FILENO);
	close(mini->fd_out);
	pid[i] = fork();
	if (pid[i] == -1)
		ft_putstr_fd("fork went wrong\n", 2);
	if (pid[i] == 0)
	{
		close(mini->main_in);
		close(mini->fd_in);
		if (mini->pipes_c[i].invalid_redir != 1 &&
		mini->pipes_c[i].error_redir != 1)
			find_command(mini->pipes_c[i].tokens,
			mini->pipes_c[i].tok_amount, mini);
		else
			close(mini->main_out);
		free_stuff(mini);
		exit(0);
	}
}

int		set_pipefd(t_mini *mini, int i)
{
	int		pipefd[mini->pipe_cmds][2];

	if (pipe(pipefd[i]) == -1)
		return (2);
	if (mini->out_redir == 0)
		mini->fd_out = pipefd[i][1];
	else
		close(pipefd[i][1]);
	mini->fd_in = pipefd[i][0];
	return (0);
}

int		execute_pipe(t_mini *mini, int *pid, int cmd)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < mini->pipe_cmds)
	{
		if (check_redir(&(mini->pipes_c[i].tokens),
		&(mini->pipes_c[i].tok_amount), mini) == -1)
			mini->c[cmd].error_redir = 1;
		var_sub(mini->pipes_c[i].tokens, mini);
		dup2(mini->fd_in, STDIN_FILENO);
		close(mini->fd_in);
		if (i == mini->pipe_cmds - 1 && mini->out_redir == 0)
			mini->fd_out = dup(mini->main_out);
		else if (i != mini->pipe_cmds - 1)
		{
			if (set_pipefd(mini, i) == 2)
				return (2);
		}
		dup_and_child(mini, pid, i);
		i++;
	}
	return (0);
}

void	set_exit_status(t_mini *mini, int **pid)
{
	int		i;
	int		j;
	int		wstat;
	pid_t	pid_wait;

	i = 0;
	while (i < mini->pipe_cmds)
	{
		pid_wait = wait(&wstat);
		j = 0;
		while ((*pid)[j])
		{
			if ((*pid)[j] == pid_wait)
				break ;
			j++;
		}
		if (WIFEXITED(wstat))
			mini->exit_int = WEXITSTATUS(wstat);
		i++;
	}
	if (*pid)
		free(*pid);
}

int		pipes(t_mini *mini, int cmd)
{
	int		*pid;
	int		i;

	i = 0;
	mini->fd_out = 1;
	if (tokenizer(mini->c[cmd].tokens, mini->c[cmd].tok_amount, mini) == -1)
		return (-1);
	pid = ft_calloc(mini->pipe_cmds, sizeof(int));
	mini->main_in = dup(STDIN_FILENO);
	mini->main_out = dup(STDOUT_FILENO);
	mini->fd_in = dup(mini->main_in);
	while (i < mini->pipe_cmds)
	{
		valid_input_redir(&mini->pipes_c[i], mini);
		i++;
	}
	if (execute_pipe(mini, pid, cmd) == 2)
		return (2);
	close(mini->fd_in);
	dup2(mini->main_in, STDIN_FILENO);
	dup2(mini->main_out, STDOUT_FILENO);
	close(mini->main_in);
	close(mini->main_out);
	set_exit_status(mini, &pid);
	return (0);
}
