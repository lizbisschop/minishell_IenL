#include "minishell.h"

int		set_fds(int i, int main_out, t_mini *mini, int *pipefd)
{
	dup2(mini->fd_in, STDIN_FILENO);
	close(mini->fd_in);
	// if last command
	if (i == mini->pipe_cmds - 1) 
	{
		// if outfile
		mini->fd_out = dup(main_out);
	}
	else
	{
		if (pipe(pipefd) == -1)
			return (2);
		mini->fd_out = pipefd[1];
		mini->fd_in = pipefd[0];
		// printf("pipe = %d\n", pipefd[0]);
	}
	dup2(mini->fd_out, STDOUT_FILENO);
	close(mini->fd_out);
	return (0);
}

int		pipes(t_mini *mini, int cmd)
{
	int		pipefd[mini->cmds][2];
	int		*pid;
	int		i;
	int		j;
	int		k;
	int		wstat;
	pid_t	pid_wait;

	i = 0;
	j = 0;
	mini->fd_out = 1000;
	tokenizer(mini->c[cmd].tokens, mini->c[cmd].tok_amount, mini);
	pid = ft_calloc(mini->pipe_cmds, sizeof(int));
	mini->main_in = dup(STDIN_FILENO);
	mini->main_out = dup(STDOUT_FILENO);
	mini->fd_in = dup(mini->main_in);
	while (j < mini->pipe_cmds) //openen van files
	{
		valid_input_redir(&mini->pipes_c[j], mini);
		j++;
	}
	while (i < mini->pipe_cmds)
	{
		check_redir(&(mini->pipes_c[i].tokens), &(mini->pipes_c[i].tok_amount), mini);
		dup2(mini->fd_in, STDIN_FILENO);
		close(mini->fd_in);
		if (i == mini->pipe_cmds - 1 && mini->out_redir == 0)
			mini->fd_out = dup(mini->main_out);
		else if (i != mini->pipe_cmds - 1)
		{
			if (pipe(pipefd[i]) == -1)
				return (2);
			if (mini->out_redir == 0)
				mini->fd_out = pipefd[i][1];
			else
				close(pipefd[i][1]);
			mini->fd_out = pipefd[i][0];
		}
		dup2(mini->fd_out, STDOUT_FILENO);
		close(mini->fd_out);
		pid[i] = fork();
		if (pid[i] == -1)
			ft_putstr_fd("fork went wrong\n", mini->main_out);
		if (pid[i] == 0)
		{
			close(mini->main_in);
			close(mini->fd_out);
			if (mini->pipes_c[i].invalid_input == 0)
				find_command(mini->pipes_c[i].tokens, mini->pipes_c[i].tok_amount, mini);
			else
				close(mini->main_out);
			free_stuff(mini);
			exit(0);
		}
		i++;
	}
	close(mini->fd_out);
	dup2(mini->main_in, STDIN_FILENO);
	dup2(mini->main_out, STDOUT_FILENO);
	close(mini->main_in);
	close(mini->main_out);
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
		if (WIFEXITED(wstat)) // if normal termination
			mini->exit_int = WEXITSTATUS(wstat);
		i++;
	}
	if (pid)
		free(pid);
	return (0);
}
