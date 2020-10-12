#include "minishell.h"

void	unset(t_mini *mini, t_command command)
{
	int		i;
	int 	tok;
	int		len;

	tok = 1;
	while (command.tokens[tok])
	{
		i = 0;
		len = ft_strlen(command.tokens[tok]);
		while (mini->env[i])
		{
			if (ft_strncmp(command.tokens[tok], mini->env[i], len) == 0)
			{
				while (mini->env[i])
				{
					if (mini->env[i + 1] != NULL)
					{
						free (mini->env[i]);
						mini->env[i] = ft_strdup(mini->env[i + 1]);
					}
					else
					{
						free (mini->env[i]);
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