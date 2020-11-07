#include "minishell.h"

void	dup_and_child(t_mini *mini, int *pid, int i)
{
	dup2(mini->fd_out, STDOUT_FILENO);
	close(mini->fd_out);
	pid[i] = fork();
	if (pid[i] == -1)
		ft_putstr_fd("fork went wrong\n", mini->main_out);
	if (pid[i] == 0)
	{
		close(mini->main_in);
		close(mini->fd_in);
		if (mini->pipes_c[i].invalid_input == 0)
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
	int		pipefd[mini->cmds][2];

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
		check_redir(&(mini->pipes_c[i].tokens),
		&(mini->pipes_c[i].tok_amount), mini);
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

void	set_in_out(t_mini *mini, int cmd, int **pid)
{
	// if (mini->pipes_c)
	// {
	// 	free_pipes_c(mini);
	// }
	mini->fd_out = 1;
	tokenizer(mini->c[cmd].tokens, mini->c[cmd].tok_amount, mini);
	(*pid) = ft_calloc(mini->pipe_cmds, sizeof(int));
	mini->main_in = dup(STDIN_FILENO);
	mini->main_out = dup(STDOUT_FILENO);
	mini->fd_in = dup(mini->main_in);
}

void	getting_exit_status(t_mini *mini, int *pid)
{
	int		i;
	int		k;
	int		wstat;
	pid_t	pid_wait;

	i = 0;
	while (i < mini->pipe_cmds)
	{
		pid_wait = wait(&wstat);
		k = 0;
		while (pid[k])
		{
			if (pid[k] == pid_wait)
				break ;
			k++;
		}
		if (WIFEXITED(wstat))
			mini->exit_int = WEXITSTATUS(wstat);
		i++;
	}
}

int		pipes(t_mini *mini, int cmd)
{
	int		*pid;
	int		j;

	j = 0;
	set_in_out(mini, cmd, &pid);
	while (j < mini->pipe_cmds)
	{
		valid_input_redir(&mini->pipes_c[j], mini);
		j++;
	}
	if (execute_pipe(mini, pid, cmd) == 2)
		return (2);
	close(mini->fd_in);
	dup2(mini->main_in, STDIN_FILENO);
	dup2(mini->main_out, STDOUT_FILENO);
	close(mini->main_in);
	close(mini->main_out);
	getting_exit_status(mini, pid);
	if (pid)
		free(pid);
	return (0);
}
