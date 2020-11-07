#include "minishell.h"

void	free_env(t_mini *mini)
{
	int i;

	i = 0;
	while (mini->env[i])
	{
		if (mini->env[i])
			free(mini->env[i]);
		i++;
	}
	if (mini->env)
		free(mini->env);
}

char	**add_to_env(char *s, t_mini *mini)
{
	char	**new_env;
	int		size;

	size = 0;
	while (mini->env[size])
	{
		size++;
	}
	new_env = ft_calloc(size + 2, sizeof(char *));
	size = 0;
	while (mini->env[size])
	{
		new_env[size] = ft_strdup(mini->env[size]);
		size++;
	}
	new_env[size] = ft_strdup(s);
	new_env[size + 1] = (void*)0;
	free_env(mini);
	return (new_env);
}

void	if_quote(int *k, int *j, t_mini *mini)
{
	if (mini->check_export == 1)
	{
		mini->export_str[*k] = '"';
		(*k)++;
	}
	mini->export_str[*k] = '\0';
	*j = 0;
	*k = 0;
	mini->check_export = 0;
	ft_putstr_fd(mini->export_str, 1);
	ft_putchar_fd('\n', 1);
	if (mini->export_str)
		free(mini->export_str);
}

void		find_right_env(t_mini *mini, int *i, int *j, int *k)
{
	while (mini->export_env[*i][*j] != '\0')
	{
		mini->export_str[*k] = mini->export_env[*i][*j];
		if (mini->export_env[*i][*j] == '=' && mini->check_export == 0)
		{
			mini->check_export = 1;
			(*k)++;
			mini->export_str[*k] = '"';
		}
		(*k)++;
		(*j)++;
	}
}

void	print_export(t_mini *mini)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	mini->check_export = 0;
	mini->export_env = sort_env(mini->env, mini);
	while (mini->export_env[i])
	{
		ft_putstr_fd("declare -x ", 1);
		mini->export_str = (char *)malloc(sizeof(char)
		* ft_strlen(mini->export_env[i]) + 3);
		find_right_env(mini, &i, &j, &k);
		if_quote(&k, &j, mini);
		i++;
	}
	free_env_export(mini);
}
