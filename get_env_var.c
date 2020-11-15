/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_env_var.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 14:35:03 by lbisscho      #+#    #+#                 */
/*   Updated: 2020/11/15 15:36:52 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void		get_env_var(int *i, char **token, t_mini *mini, char **str)
{
	int		var_length;
	int		j;
	char	*s;

	var_length = 0;
	j = 0;
	(*i)++;
	if ((*token)[*i] == '"' || (*token)[*i] == '\'')
		var_length = dollar_quote(i, token, mini, str);
	else
	{
		while ((*token)[(*i) + var_length] != '\0' && (ft_isalnum((*token)[(*i)
		+ var_length]) || (*token)[(*i) + var_length] == '_'))
			var_length++;
		while (mini->env[j])
		{
			if (ft_strncmp(&(*token)[(*i)], mini->env[j], var_length) == 0 &&
			mini->env[j][var_length] == '=')
				(*str) = gnl_strjoin((*str), &(mini->env[j][var_length + 1]));
			j++;
		}
	}
	(*i) += var_length;
}
