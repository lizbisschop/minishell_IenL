#include "minishell.h"

int ft_return(t_mini *mini)
{
	// free_stuff(mini);
	(void)mini;
	return (0);
}


void free_stuff(t_mini *mini)
{
	int i;
	int j;

	j = 0;
	while (j < mini->cmds)
	{
		i = 0;
		while (mini->c[j].tokens[i])
		{
			free(mini->c[j].tokens[i]);
			i++;
		}
		if (mini->c[j].tokens)
			free(mini->c[j].tokens);
		j++;
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
	if (mini->sp_input)
		free(mini->sp_input);
}