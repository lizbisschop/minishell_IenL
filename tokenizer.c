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
		ft_putstr_fd("Malloc fail\n", 2);
		exit(1);
	}
	while (k < n)
	{
		j = 0;
		mini->pipes_c[k].invalid_input = 0;
		tok_n = pipe_tok_amount(tokens, i, tok_amount);
		// printf("tok_n=%d\n", tok_n);
		mini->pipes_c[k].tok_amount = tok_n;
		mini->pipes_c[k].tokens = (char **)malloc((tok_n + 1) * sizeof(char *));
		if (!mini->pipes_c[k].tokens)
			return (-1);
		while (j < tok_n)
		{
			mini->pipes_c[k].tokens[j] = ft_strdup(tokens[i]);
			if (!mini->pipes_c[k].tokens[j])
				return (-1);
			// printf("[%s]\n", mini->pipes_c[k].tokens[j]);
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
