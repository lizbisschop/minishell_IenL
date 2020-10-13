#include "minishell.h"

char	**tokenizer(t_mini *mini, int cmd)
{
	int		i;
	int		j;
	char	**str;

	i = 0;
	j = 0;
	while (i < mini->c[cmd].tok_amount)
	{
		if (ft_strncmp(mini->c[cmd].tokens[i], "|", 1) == 0
		&& ft_strlen(mini->c[cmd].tokens[i]) == 1)
			break ;
		i++;
	}
	str = (char **)malloc(i * sizeof(char *));
	while (j < i)
	{
		str[j] = ft_strdup(mini->c[cmd].tokens[j]);
		j++;
	}
	return (str);
}

int		pipes(t_mini *mini, int cmd)
{
	int		pipefd[2];
	int		pids[2];
	int		i;
	int		main_in;
	int		main_out;
	// char	**tokens;
	// extern char **environ;

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
	printf("pids[0] = [%d] | pids[1] = [%d]\n", pids[0], pids[1]);
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
		printf("wait for pid: [%d]\n", pids[i]);
		waitpid(pids[i], NULL, 0);
		i++;
	}
	(void)mini;
	(void)cmd;
	return (0);
}
