#include "minishell.h"

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
			return (i);
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
		mini->pipes_c[k].tok_amount = tok_n;
		mini->pipes_c[k].tokens = (char **)malloc(tok_n * sizeof(char *));
		while (j < tok_n)
		{
			mini->pipes_c[k].tokens[j] = ft_strdup(tokens[i]);
			printf("[%s]\n", mini->pipes_c[k].tokens[j]);
			i++;
			j++;
		}
		printf("\n");
		i++;
		k++;
	}
	return (0);
}

int		pipes(t_mini *mini, int cmd)
{
	int		pipefd[2];
	int		pids[2];
	int		i;
	int		main_in;
	int		main_out;

	tokenizer(mini->c[cmd].tokens, mini->c[cmd].tok_amount, mini);
	if (pipe(pipefd) == -1)
		return (2);
	main_in = dup(STDIN_FILENO);
	main_out = dup(STDOUT_FILENO);
	while (i < 2)
	{
		pids[i] = fork();
		if (pids[i] < 0)
			return (2);
		if (pids[i] == 0)
			break ;
		i++;
	}
	i = 0;
	// printf("pids[0] = [%d] | pids[1] = [%d]\n", pids[0], pids[1]);
	while (i < 2)
	{
		if (pids[i] == 0 && i == 0)
		{
			close(pipefd[0]);
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
			// find_command();
			// tokens = tokenizer(mini, cmd);
			// execve(tokens[0], tokens, environ);
			exit (0);
		}
		if (pids[i] == 0 && i == 1)
		{
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
			// find_command();
			// tokens = tokenizer(mini, cmd);
			// execve(tokens[0], tokens, environ);
			exit (0);
		}
		i++;
	}
	close(main_in);
	close(main_out);
	i = 0;
	while (i < 2)
	{
		// printf("wait for pid: [%d]\n", pids[i]);
		waitpid(pids[i], NULL, 0);
		i++;
	}
	(void)mini;
	(void)cmd;
	return (0);
}
