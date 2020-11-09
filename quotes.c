/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quotes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 18:18:39 by iboeters      #+#    #+#                 */
/*   Updated: 2020/11/09 18:21:16 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	else_slash(char **s, char **str, int *i, int *j)
{
	(*str)[*j] = (*s)[*i];
	(*j)++;
}

void	fill_str_char(char **s, char **str, int *i, int *j)
{
	char q;

	q = '\0';
	while ((*s)[*i] != '\0')
	{
		if ((*s)[*i] == '\'' || (*s)[*i] == '"')
		{
			q = (*s)[*i];
			(*i)++;
			while ((*s)[*i] != q && (*s)[*i] != '\0')
			{
				if (q == '"' && (*s)[*i] == '\\' && ((*s)[*i + 1] == q
				|| (*s)[*i + 1] == '\\' || (*s)[*i + 1] == '$'))
					(*i)++;
				(*str)[*j] = (*s)[*i];
				(*j)++;
				*i = ((*s)[*i] != '\0') ? *i + 1 : *i;
			}
		}
		else if ((*s)[*i] != '\\')
			else_slash(s, str, i, j);
		(*i)++;
	}
}

char	*fill_string(int len, char **s, t_mini *mini)
{
	char	q;
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	q = '\0';
	str = (char *)malloc(sizeof(char) * (len - mini->n_quotes + 1));
	if (!str)
	{
		ft_putstr_fd("malloc failed\n", 2);
		exit(1);
	}
	fill_str_char(s, &str, &i, &j);
	str[j] = '\0';
	if (*s)
	{
		free(*s);
		*s = NULL;
	}
	return (str);
}

char	*unquote(char **s, t_mini *mini)
{
	char	q;
	char	anti_q;
	char	temp;
	int		i;

	i = 0;
	q = '\'';
	anti_q = '"';
	mini->n_quotes = 0;
	while ((*s)[i] != '\0')
	{
		if ((*s)[i] == q)
			mini->n_quotes++;
		else if ((*s)[i] == '\\' && (*s)[i + 1] != '\0')
			i++;
		else if ((*s)[i] == anti_q && mini->n_quotes % 2 == 0)
		{
			mini->n_quotes++;
			temp = q;
			q = anti_q;
			anti_q = temp;
		}
		i++;
	}
	return (fill_string(i, s, mini));
}

void	quotes(char **tokens, t_mini *mini)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		tokens[i] = unquote(&(tokens[i]), mini);
		i++;
	}
}
