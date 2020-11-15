/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 18:17:51 by iboeters      #+#    #+#                 */
/*   Updated: 2020/11/15 17:06:38 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		loop_env(t_mini *mini, char **str, char *s, int *i)
{
	int len;
	int j;

	j = 0;
	len = 0;
	while (mini->env[j])
	{
		len = 0;
		while (mini->env[j][len] != '\0' && mini->env[j][len] != '=')
			len++;
		if (ft_strncmp(s, mini->env[j], len) == 0 && *i == len)
		{
			if (mini->env[j])
				free(mini->env[j]);
			mini->env[j] = ft_strdup(s);
			if (*str)
				free(*str);
			return (1);
		}
		j++;
	}
	return (0);
}

int		check_over_write(char *s, t_mini *mini)
{
	int		i;
	int		j;
	int		len;
	char	*str;

	i = 0;
	j = 0;
	while (s[i] != '\0' && s[i] != '=')
		i++;
	str = (char *)malloc(sizeof(char) * i + 1);
	if (!str)
		malloc_error();
	i = 0;
	while (s[i] != '\0' && s[i] != '=')
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	if (loop_env(mini, &str, s, &i) == 1)
		return (1);
	if (str)
		free(str);
	return (0);
}

void	correct_export(char **tokens, t_mini *mini, int i)
{
	if (tokens[i][0] == '=')
	{
		ft_putstr_fd("bash: export: `", 2);
		ft_putstr_fd(tokens[i], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		mini->exit_int = 1;
		return ;
	}
	if (check_over_write(tokens[i], mini) == 0)
		mini->env = add_to_env(tokens[i], mini);
}

int		is_al_num_export(char **tokens, t_mini *mini, int i, int *j)
{
	while (tokens[i][*j] != '\0' && tokens[i][*j] != '=')
	{
		if ((ft_isalnum(tokens[i][*j]) == 0 && tokens[i][*j] != '_')
		|| (ft_isdigit(tokens[i][*j]) == 1 && *j == 0))
		{
			ft_putstr_fd("bash: export: `", 2);
			ft_putstr_fd(tokens[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			mini->exit_int = 1;
			return (1);
		}
		(*j)++;
	}
	return (0);
}

void	ft_export(char **tokens, int tok_amount, t_mini *mini)
{
	int i;
	int j;

	i = 1;
	j = 0;
	if (tok_amount != 1)
	{
		while (tokens[i])
		{
			if (is_al_num_export(tokens, mini, i, &j) != 1)
				correct_export(tokens, mini, i);
			j = 0;
			i++;
		}
	}
	if (i == 1)
		print_export(mini);
}
