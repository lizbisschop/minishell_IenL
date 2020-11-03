#include "minishell.h"

void	free_sp_input(t_mini *mini)
{
	int i;

	i = 0;
	printf("her I am\n");
	printf("%s\n", mini->sp_input[0]);
	while (mini->sp_input[i])
	{
		printf("hello\n");
		if (mini->sp_input[i])
			free(mini->sp_input[i]);
		i++;
	}
	if (mini->sp_input)
		free(mini->sp_input);
}

void	free_stuff(t_mini *mini)
{
	int i;
	int j;

	j = 0;
	while (j < mini->cmds)
	{
		i = 0;
		if (mini->c != 0)
		{
			while (mini->c[j].tokens[i])
			{
				if (mini->c[j].tokens[i])
					free(mini->c[j].tokens[i]);
				i++;
			}
			if (mini->c[j].tokens)
				free(mini->c[j].tokens);
			j++;
		}
		else
			break ;
	}
	if (mini->c)
		free(mini->c);
	j = 0;
	while (j < mini->cmds)
	{
		if (mini->sp_input[j])
			free(mini->sp_input[j]);
		j++;
	}
	j = 0;
	while (j < mini->pipe_cmds)
	{
		i = 0;
		if (mini->pipes_c != 0)
		{
			while (mini->pipes_c[j].tokens[i])
			{
				if (mini->pipes_c[j].tokens[i])
					free(mini->pipes_c[j].tokens[i]);
				i++;
			}
			if (mini->pipes_c[j].tokens)
				free(mini->pipes_c[j].tokens);
			j++;
		}
		else
			break ;
	}
	if (mini->sp_input)
		free(mini->sp_input);
}
