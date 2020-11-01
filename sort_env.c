#include "minishell.h"

void	free_env_export(t_mini *mini)
{
	int i;

	i = 0;
	while (mini->export_env[i])
	{
		if (mini->export_env[i])
			free(mini->export_env[i]);
		i++;
	}
	if (mini->export_env)
		free(mini->export_env);
}

char **sort_env(char **str, t_mini *mini)
{
	char *alphabet;
	int i;
	int j;
	int alpha;
	char **new;

	i = 0;
	j = 0;
	alpha = 0;
	alphabet = ft_strdup("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
	while (str[i])
		i++;
	new = ft_calloc(i, sizeof(char *));
	i = 0;
	while (alphabet[alpha] != '\0')
	{
		while (str[i])
		{
			if (str[i][0] == alphabet[alpha])
			{
		// printf("hallllo\n");
			// printf("[%c], [%c]\n", str[i][0], alphabet[alpha]);
				new[j] = ft_strdup(str[i]);
				j++;
			}	
			i++;
		}
		alpha++;
		i = 0;
	}
	if (alphabet)
		free (alphabet);
	return (new);
}