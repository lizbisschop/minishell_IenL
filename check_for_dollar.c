/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_for_dollar.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 18:16:11 by iboeters      #+#    #+#                 */
/*   Updated: 2020/11/09 18:16:14 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		get_env_var(int *i, char **token, t_mini *mini, char **str)
{
	int		var_length;
	int		j;

	var_length = 0;
	j = 0;
	(*i)++;
	if ((*token)[*i] == '_')
	{
		*token = ft_strdup("");
		return ;
	}
	while ((*token)[(*i) + var_length] != '\0' && ft_isalnum((*token)[(*i) +
	var_length]))
		var_length++;
	while (mini->env[j])
	{
		if (ft_strncmp(&(*token)[(*i)], mini->env[j], var_length) == 0 &&
		mini->env[j][var_length] == '=')
			(*str) = gnl_strjoin((*str), &(mini->env[j][var_length + 1]));
		j++;
	}
	(*i) += var_length;
}

void		set_open_q(char token, char *q, int *n_quotes)
{
	char	anti_q;
	char	temp;

	if (q[0] == '\'')
		anti_q = '"';
	else
		anti_q = '\'';
	if (token == q[0])
		(*n_quotes)++;
	else if (token == anti_q && (*n_quotes) % 2 == 0)
	{
		(*n_quotes)++;
		temp = q[0];
		q[0] = anti_q;
		anti_q = temp;
	}
}

void		strjoin_char(int *i, char **str, char **token)
{
	char	c[2];

	c[0] = (*token)[*i];
	c[1] = '\0';
	*str = gnl_strjoin(*str, c);
	(*i)++;
}

int			dollar_type(char **token, t_mini *mini, char **str)
{
	int		i;
	char	q;
	int		n_quotes;
	char	c[2];

	i = 0;
	q = '"';
	n_quotes = 0;
	while ((*token)[i] != '\0')
	{
		set_open_q((*token)[i], &q, &n_quotes);
		if ((*token)[i] == '$' && (*token)[i + 1] == '?' && q != '\'')
		{
			mini->nbr = ft_itoa(mini->exit_int);
			*str = gnl_strjoin(*str, mini->nbr);
			i += 2;
		}
		else if ((*token)[i] == '$' && !ft_isalnum((*token)[i + 1]))
			return (-1);
		else if ((*token)[i] == '$' && (*token)[i + 1] && q != '\'')
			get_env_var(&i, token, mini, str);
		else
			strjoin_char(&i, str, token);
	}
	return (0);
}

void		check_for_dollar(char **token, t_mini *mini)
{
	char *str;

	mini->nbr = NULL;
	str = ft_strdup("");
	if (ft_strchr(*token, '$'))
	{
		if (dollar_type(token, mini, &str) == -1)
			return ;
		if (*token)
			free(*token);
		(*token) = ft_strdup(str);
		if (str)
			free(str);
		if (mini->nbr)
			free(mini->nbr);
	}
	else
	{
		if (str)
			free(str);
	}
}
