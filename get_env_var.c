/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_env_var.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 14:35:03 by lbisscho      #+#    #+#                 */
/*   Updated: 2020/11/22 15:55:34 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		dollar_questionmark(t_mini *mini, char **str, int *i)
{
	mini->nbr = ft_itoa(mini->exit_int);
	*str = gnl_strjoin(*str, mini->nbr);
	*i += 2;
}

int			dollar_quote(int *i, char **token, t_mini *mini, char **str)
{
	char	*s;
	int		var_length;

	var_length = 0;
	while ((*token)[(*i) + var_length] != '\0' &&
	(*token)[(*i) + var_length] != '$')
		var_length++;
	s = ft_substr(*token, *i, var_length);
	(*str) = gnl_strjoin((*str), s);
	if (s)
		free(s);
	return (var_length);
}

void		env_found(t_mini *mini, int var_length, char **str, int *i)
{
	if (mini->piped == 1)
	{
		if (mini->n_quotes % 2 != 0 ||
		(ft_strncmp(mini->pipes_c[mini->cmd].tokens[0], "export", 6) == 0
		&& ft_strlen(mini->pipes_c[mini->cmd].tokens[0]) == 6))
			(*str) = gnl_strjoin((*str),
			&(mini->env[mini->env_i][var_length + 1]));
		else
			expand_tokens_pipes(mini, str, *i - 1,
			&(mini->env[mini->env_i][var_length + 1]));
	}
	else
	{
		if (mini->n_quotes % 2 != 0 ||
		(ft_strncmp(mini->c[mini->cmd].tokens[0], "export", 6) == 0
		&& ft_strlen(mini->c[mini->cmd].tokens[0]) == 6))
			(*str) = gnl_strjoin((*str),
			&(mini->env[mini->env_i][var_length + 1]));
		else
			expand_tokens(mini, str, *i - 1,
			&(mini->env[mini->env_i][var_length + 1]));
	}
}

void		get_env_var(int *i, char **token, t_mini *mini, char **str)
{
	int		var_length;

	var_length = 0;
	(*i)++;
	mini->env_i = 0;
	while ((*token)[(*i) + var_length] != '\0' && (ft_isalnum((*token)[(*i)
	+ var_length]) || (*token)[(*i) + var_length] == '_'))
		var_length++;
	while (mini->env[mini->env_i])
	{
		if (ft_strncmp(&(*token)[(*i)], mini->env[mini->env_i], var_length)
		== 0 && mini->env[mini->env_i][var_length] == '=')
			env_found(mini, var_length, str, i);
		mini->env_i++;
	}
	(*i) += var_length;
}
