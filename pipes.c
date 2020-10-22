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

void	print_pipeinput_terminal(int main_out)
{
	char	buf[100 + 1];
	char	*str;
	int		ret;

	str = ft_strdup("");
	ret = 0;
	while (ret = read(STDIN_FILENO, buf, 100))
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
	int		pid;
	int		i;
	int		main_in;
	int		main_out;
	int		fd_in;
	int		fd_out;
	int		ret;

	i = 0;
	fd_out = 1000;
	// free stuff in pipes_c
	printf("cmd=%d\n", cmd);
	tokenizer(mini->c[cmd].tokens, mini->c[cmd].tok_amount, mini);
	main_in = dup(STDIN_FILENO);
	main_out = dup(STDOUT_FILENO);
	mini->main_in = main_in;
	mini->main_out = main_out;
	// setup first cmd
	ret = check_input_redir(&fd_in, &(mini->pipes_c[cmd].tokens));
	if (ret == 0)
		fd_in = dup(main_in);		
	printf("m_in\t%d\nm_out\t%d\nf_in\t%d\nf_out\t%d\n", main_in, main_out, fd_in, fd_out);
	while (i < mini->pipe_cmds)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
		// if last command
		if (i == mini->pipe_cmds - 1)
		{
			// if outfile
			// check_output_redir()
			fd_out = dup(main_out);
		}
		else
		{
			if (pipe(pipefd[i]) == -1)
				return (2);
			fd_out = pipefd[i][1];
			fd_in = pipefd[i][0];
			// printf("pipe = %d\n", pipefd[0]);
		}
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
		pid = fork();
		if (pid == -1)
			ft_putstr_fd("fork went wrong\n", main_out);
		if (pid == 0)
		{
			// Child process
			// open fd's: main_in, main_out, fd_in
			// close(fd_out); // hoeft niet door close(fd_out)
			close(main_in);
			close(fd_in);
			if (i != 0 || ret != -1)
				find_command(mini->pipes_c[i].tokens, mini->pipes_c[i].tok_amount, mini);
			exit(0);
		}
		// print_pipeinput_terminal(main_out);
		// ft_putstr_fd("thank you, next\n", main_out);
		i++;
	}
	close(fd_in);
	dup2(main_in, STDIN_FILENO);
	dup2(main_out, STDOUT_FILENO);
	close(main_in);
	close(main_out);
	while (wait(NULL) != -1)
	{
	}
	return (0);
}

// ft_putstr_fd(mini->pipes_c[i].tokens[0], main_out);
// ft_putstr_fd("\t", main_out);
// ft_putstr_fd(mini->pipes_c[i].tokens[1], main_out);
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