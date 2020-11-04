#include "minishell.h"

int		set_fds(int *fd_in, int i, int *fd_out, int main_out, t_mini *mini, int *pipefd)
{
	dup2(*fd_in, STDIN_FILENO);
	close(*fd_in);
	// if last command
	if (i == mini->pipe_cmds - 1) 
	{
		// if outfile
		*fd_out = dup(main_out);
	}
	else
	{
		if (pipe(pipefd) == -1)
			return (2);
		*fd_out = pipefd[1];
		*fd_in = pipefd[0];
		// printf("pipe = %d\n", pipefd[0]);
	}
	dup2(*fd_out, STDOUT_FILENO);
	close(*fd_out);
	return (0);
}

void	print_pipeinput_terminal(int main_out)
{
	char	buf[100 + 1];
	char	*str;
	int		ret;

	str = ft_strdup("");
	ret = 0;
	while ((ret = read(STDIN_FILENO, buf, 100)))
	{
		buf[ret] = '\0';
		str = ft_strjoin(str, buf);
	}
	ft_putstr_fd("content STDIN_FILENO: ", main_out);
	ft_putstr_fd(str, main_out);
	ft_putchar_fd('\n', main_out);
}

int		pipes(t_mini *mini, int cmd)
{
	int		pipefd[mini->cmds][2];
	int		*pid;
	int		i;
	int		j;
	int		k;
	int		main_in;
	int		main_out;
	int		fd_in;
	int		fd_out;
	int		wstat;
	pid_t	pid_wait;

	i = 0;
	j = 0;
	fd_out = 1000;
	// free stuff in pipes_c
	tokenizer(mini->c[cmd].tokens, mini->c[cmd].tok_amount, mini);
	pid = ft_calloc(mini->pipe_cmds, sizeof(int));
	main_in = dup(STDIN_FILENO);
	main_out = dup(STDOUT_FILENO);
	mini->main_in = main_in;
	mini->main_out = main_out;
	fd_in = dup(main_in);
	// printf("m_in\t%d\nm_out\t%d\nf_in\t%d\nf_out\t%d\n", main_in, main_out, fd_in, fd_out);
	while (j < mini->pipe_cmds) //openen van files
	{
		valid_input_redir(&mini->pipes_c[j], mini);
		j++;
	}
	while (i < mini->pipe_cmds)
	{
		check_redir(&fd_out, &fd_in, &(mini->pipes_c[i].tokens), &(mini->pipes_c[i].tok_amount), mini);
		ft_putstr_fd("mini->in_redir = ", main_out);
		ft_putnbr_fd(mini->in_redir, main_out);
		ft_putstr_fd("\nmini->out_redir = ", main_out);
		ft_putnbr_fd(mini->out_redir, main_out);
		ft_putstr_fd("\n", main_out);
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
		if (i == mini->pipe_cmds - 1 && mini->out_redir == 0)
			fd_out = dup(main_out);
		else if (i != mini->pipe_cmds - 1)
		{
			if (pipe(pipefd[i]) == -1)
				return (2);
			if (mini->out_redir == 0)
				fd_out = pipefd[i][1];
			else
				close(pipefd[i][1]);
			fd_in = pipefd[i][0];
		}
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
		pid[i] = fork();
		if (pid[i] == -1)
			ft_putstr_fd("fork went wrong\n", main_out);
		if (pid[i] == 0)
		{
			// Child process
			// open fd's: main_in, main_out, fd_in
			close(main_in);
			close(fd_in);
			// print_pipeinput_terminal(main_out);
			if (mini->pipes_c[i].invalid_input == 0)
				find_command(mini->pipes_c[i].tokens, mini->pipes_c[i].tok_amount, mini);
			else
				close(main_out);
			free_stuff(mini);
			exit(0);
		}
		i++;
	}
	close(fd_in);
	dup2(main_in, STDIN_FILENO);
	dup2(main_out, STDOUT_FILENO);
	close(main_in);
	close(main_out);
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
