/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_for_dollar.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 18:16:11 by iboeters      #+#    #+#                 */
/*   Updated: 2020/11/15 15:32:40 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		set_open_q(char token, char *q, t_mini *mini)
{
	char	anti_q;
	char	temp;

	if (q[0] == '\'')
		anti_q = '"';
	else
		anti_q = '\'';
	if (token == q[0])
		(mini->n_quotes)++;
	else if (token == anti_q && (mini->n_quotes) % 2 == 0)
	{
		mini->n_quotes++;
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

void		dollar_questionmark(t_mini *mini, char **str, int *i)
{
	mini->nbr = ft_itoa(mini->exit_int);
	*str = gnl_strjoin(*str, mini->nbr);
	*i += 2;
}

int			dollar_type(char **token, t_mini *mini, char **str)
{
	int		i;
	char	q;
	char	c[2];

	i = 0;
	q = '"';
	mini->n_quotes = 0;
	while ((*token)[i] != '\0')
	{
		set_open_q((*token)[i], &q, mini);
		if ((*token)[i] == '$' && (*token)[i + 1] == '?' && q != '\'')
			dollar_questionmark(mini, str, &i);
		else if ((*token)[i] == '$' && (*token)[i + 1] != '\0' &&
		!(ft_isalnum((*token)[i + 1]) || (*token)[i + 1] == '"' ||
		(*token)[i + 1] == '\'') && (*token)[i + 1] != '_')
			return (-1);
		else if ((*token)[i] == '$' && (*token)[i + 1] &&
		q != '\'' && !((*token)[i + 1] == '"' && mini->n_quotes % 2 != 0))
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
		{
			if (str)
				free(str);
			return ;
		}
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
