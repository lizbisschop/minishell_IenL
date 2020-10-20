#include "minishell.h"

/*
** enkele pipe meegeven
*/

int		pipe_amount(char **tokens, int tok_amount)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	while (i < tok_amount)
	{
		if (ft_strncmp(tokens[i], "|", 1) == 0
		&& ft_strlen(tokens[i]) == 1)
			n++;
		i++;
	}
	return (n + 1);
}

int		pipe_tok_amount(char **tokens, int i, int tok_amount)
{
	int		ret;

	ret = 0;
	while (i < tok_amount)
	{
		if (ft_strncmp(tokens[i], "|", 1) == 0
		&& ft_strlen(tokens[i]) == 1)
			return (ret);
		i++;
		ret++;
	}
	return (ret);
}

int		tokenizer(char **tokens, int tok_amount, t_mini *mini)
{
	int		i;
	int		j;
	int		k;
	int		n;
	int		tok_n;

	i = 0;
	k = 0;
	tok_n = 0;
	n = pipe_amount(tokens, tok_amount);
	mini->pipe_cmds = n;
	mini->pipes_c = (t_command *)malloc(sizeof(t_command) * (n + 1));
	if (mini->pipes_c == (void*)-1)
	{
		ft_putstr_fd("Malloc fail\n", 1);
		exit(0);
	}
	while (k < n)
	{
		j = 0;
		tok_n = pipe_tok_amount(tokens, i, tok_amount);
		printf("tok_n=%d\n", tok_n);
		mini->pipes_c[k].tok_amount = tok_n;
		mini->pipes_c[k].tokens = (char **)malloc((tok_n + 1) * sizeof(char *));
		while (j < tok_n)
		{
			mini->pipes_c[k].tokens[j] = ft_strdup(tokens[i]);
			printf("[%s]\n", mini->pipes_c[k].tokens[j]);
			i++;
			j++;
		}
		// printf("\n");
		mini->pipes_c[k].tokens[j] = NULL;
		i++; // for | token
		k++;
	}
	return (0);
}

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

int		forkeee()
{
	return (fork());
}

int		pipes(t_mini *mini, int cmd)
{
	int		pipefd[mini->cmds][2];
	int		pid;
	int		i;
	int		main_in;
	int		main_out;
	int		fd_in;
	int		fd_out;

	i = 0;
	// free stuff in pipes_c
	printf("cmd=%d\n", cmd);
	tokenizer(mini->c[cmd].tokens, mini->c[cmd].tok_amount, mini);
	main_in = dup(STDIN_FILENO);
	main_out = dup(STDOUT_FILENO);
	mini->main_in = main_in;
	mini->main_out = main_out;
	// if infile
	fd_in = dup(main_in);
	while (i < mini->pipe_cmds)
	{
		set_fds(&fd_in, i, &fd_out, main_out, mini, pipefd[i]);
		ft_putstr_fd("liz\n", main_out);
		pid = forkeee();
		if (pid == -1)
		{
			ft_putstr_fd("fork wrong\n", main_out);
		}
		ft_putstr_fd("iris\n", main_out);
		// write(main_out, ft_itoa(pid), ft_strlen(ft_itoa(pid)));
		// write(main_out, "\n", 1);
		if (pid == 0)
		{
			ft_putstr_fd("jazeker\n", main_out);
			// Child process
			// close(fd_out); // hoeft niet door close(fd_out)
			// close(fd_in);
			// close(main_in);
			// ft_putstr_fd(mini->pipes_c[i].tokens[0], main_out);
			// ft_putstr_fd("\t", main_out);
			// // ft_putstr_fd(mini->pipes_c[i].tokens[1], main_out);
			// ft_putstr_fd("\n", main_out);
			// ft_putstr_fd("out = ", main_out);
			// ft_putstr_fd(ft_itoa(fd_out), main_out);
			// ft_putstr_fd(" & in = ", main_out);
			// ft_putstr_fd(ft_itoa(fd_in), main_out);
			// ft_putstr_fd("\n", main_out);
			// ft_putstr_fd("i = ", main_out);
			// ft_putstr_fd(ft_itoa(i), main_out);
			// ft_putstr_fd("\ntok_amount=", main_out);
			// ft_putstr_fd(ft_itoa(mini->pipes_c[i].tok_amount), main_out);
			// ft_putstr_fd("\n", main_out);
			// find_command(mini->pipes_c[i].tokens, mini->pipes_c[i].tok_amount, mini);
			// ft_putstr_fd("\n\n", main_out);
			// // close(main_out);
			// ft_putstr_fd("oi\n", main_out);
			// sleep (9);
			// system("ps");
			exit(0);
		}
		ft_putstr_fd("wait\n", main_out);
		waitpid(pid, NULL, 0);
		i++;
	}
	dup2(main_in, STDIN_FILENO);
	dup2(main_out, STDOUT_FILENO);
	close(main_in);
	close(main_out);
	while (wait(NULL) != -1)
	{
	}
	return (0);
}
