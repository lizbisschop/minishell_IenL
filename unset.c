#include "minishell.h"

void	unset(char **tokens, t_mini *mini)
{
	int		i;
	int		tok;
	int		len;

	tok = 1;
	while (tokens[tok])
	{
		i = 0;
		len = ft_strlen(tokens[tok]);
		while (mini->env[i])
		{
			if (ft_strncmp(tokens[tok], mini->env[i], len) == 0)
			{
				while (mini->env[i])
				{
					free(mini->env[i]);
					if (mini->env[i + 1] != NULL)
						mini->env[i] = ft_strdup(mini->env[i + 1]);
					else
					{
						free(mini->env[i]);
						mini->env[i] = NULL;
						break ;
					}
					i++;
				}
			}
			if (mini->env[i] == NULL)
				break ;
			i++;
		}
		tok++;
	}
}
