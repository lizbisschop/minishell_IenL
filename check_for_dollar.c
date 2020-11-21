/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_for_dollar.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 18:16:11 by iboeters      #+#    #+#                 */
/*   Updated: 2020/11/21 11:56:47 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		set_open_q(char token, t_mini *mini)
{
	char	anti_q;
	char	temp;

	if (mini->q == '\'')
		anti_q = '"';
	else
		anti_q = '\'';
	if (token == mini->q)
		(mini->n_quotes)++;
	else if (token == anti_q && (mini->n_quotes) % 2 == 0)
	{
		mini->n_quotes++;
		temp = mini->q;
		mini->q = anti_q;
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

void		dollar_num(char **token, int *i, t_mini *mini, char **str)
{
	int		var_length;
	char	*s;

	var_length = 0;
	(*i) += 2;
	while ((*token)[*i + var_length] != '\0' &&
	(*token)[*i + var_length] != '$')
		var_length++;
	s = ft_substr(*token, *i, var_length);
	if (!s)
		malloc_error();
	(*str) = gnl_strjoin(*str, s);
	if (s)
		free(s);
	(*i) += var_length;
}

int			dollar_type(char **token, t_mini *mini, char **str)
{
	int		i;

	i = 0;
	mini->q = '"';
	mini->n_quotes = 0;
	while ((*token)[i] != '\0')
	{
		set_open_q((*token)[i], mini);
		if ((*token)[i] == '\\' && mini->q == '"')
		{
			i++;
			if ((*token)[i] == '$')
				strjoin_char(&i, str, token);
		}
		else if ((*token)[i] == '$' && (*token)[i + 1] == '?' && mini->q != '\'')
			dollar_questionmark(mini, str, &i);
		else if ((*token)[i] == '$' && (*token)[i + 1] != '\0' &&
		!(ft_isalnum((*token)[i + 1]) || (*token)[i + 1] == '"' ||
		(*token)[i + 1] == '\'') && (*token)[i + 1] != '_')
			return (-1);
		else if ((*token)[i] == '$' && ft_isdigit((*token)[i + 1])
		&& (mini->q != '\'' || mini->n_quotes % 2 == 0))
			dollar_num(token, &i, mini, str);
		else if ((*token)[i] == '$' && (*token)[i + 1] != '\0' &&
		(mini->q != '\'' || mini->n_quotes % 2 == 0) &&
		!((*token)[i + 1] == '"' && mini->n_quotes % 2 != 0))
			get_env_var(&i, token, mini, str);
		else
			strjoin_char(&i, str, token);
	}
	if (mini->piped == 1)
		mini->pipes_c[mini->cmd].tokens[mini->i_tok] = ft_strdup(*str);
	else
		mini->c[mini->cmd].tokens[mini->i_tok] = ft_strdup(*str);
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
		{
			if (str)
				free(str);
			return ;
		}
		if (*token)
			free(*token);
		(*token) = ft_strdup(str);
		if (ft_strlen(*token) == 0)
		{
			//trim tokens: if env doesnt exist, remove token
		}
		// if (str)
		// 	free(str);
		if (mini->nbr)
			free(mini->nbr);
	}
	else
	{
		if (str)
			free(str);
	}
}
