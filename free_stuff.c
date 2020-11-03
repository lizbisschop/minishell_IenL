#include "minishell.h"

void free_stuff(t_mini *mini)
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
	if (mini->sp_input[j])
	{
		while (mini->sp_input[j])
		{
			if (mini->sp_input[j])
				free(mini->sp_input[j]);
			j++;
		}
	}
	// j = 0;
	// while (j < mini->pipe_cmds)
	// {
	// 	i = 0;
	// 	if (mini->pipes_c != 0)
	// 	{
	// 		while (mini->pipes_c[j].tokens[i])
	// 		{
	// 			if (mini->pipes_c[j].tokens[i])
	// 				free(mini->pipes_c[j].tokens[i]);
	// 			i++;
	// 		}
	// 		if (mini->pipes_c[j].tokens)
	// 			free(mini->pipes_c[j].tokens);
	// 		j++;
	// 	}
	// 	else
	// 		break ;
	// }
	if (mini->sp_input)
		free(mini->sp_input);
}
