/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 18:17:54 by iboeters      #+#    #+#                 */
/*   Updated: 2020/11/15 14:48:35 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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

void	add_quotes(t_mini *mini, int i)
{
	int		j;
	int		k;

	j = 0;
	k = 0;
	while (mini->env[mini->arr[i]][j] != '\0')
	{
		mini->export_str[k] = mini->env[mini->arr[i]][j];
		if (mini->env[mini->arr[i]][j] == '=' && mini->check_export == 0)
		{
			mini->check_export = 1;
			k++;
			mini->export_str[k] = '"';
		}
		k++;
		j++;
	}
	if (mini->check_export == 1)
	{
		mini->export_str[k] = '"';
		k++;
	}
	mini->export_str[k] = '\0';
}

void	print_export(t_mini *mini)
{
	int i;
	int j;
	int k;

	i = 0;
	mini->arr = sort_env(mini->env);
	while (mini->env[i])
	{
		mini->check_export = 0;
		j = 0;
		k = 0;
		ft_putstr_fd("declare -x ", 1);
		mini->export_str = (char *)malloc(sizeof(char)
		* ft_strlen(mini->env[mini->arr[i]]) + 3);
		if (!mini->export_str)
			malloc_error();
		add_quotes(mini, i);
		ft_putstr_fd(mini->export_str, 1);
		ft_putchar_fd('\n', 1);
		if (mini->export_str)
			free(mini->export_str);
		i++;
	}
	if (mini->arr)
		free(mini->arr);
}
