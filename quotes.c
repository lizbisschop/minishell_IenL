/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quotes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/17 16:04:20 by iboeters      #+#    #+#                 */
/*   Updated: 2020/09/21 18:51:32 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** CHANGE SO THAT QUOTES IN BETWEEN OTHER QUOTES DONT GET COUNTED
*/

int		multi_lines(char *str)
{
	int i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"')
			count++;
		i++;
	}
	if (count % 2)
		return (1);
	return (0);
}

char	*fill_string(int n_quotes, char c, char *line, t_mini *mini)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = (char *)malloc((mini->end_string - n_quotes + 1) * sizeof(char));
	while (i < mini->end_string)
	{
		if (line[i] != c)
		{
			str[j] = line[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
	return (str);
}

char	*unquote(char *line, t_mini *mini, int begin, int command)
{
	int		n_quotes;
	char	c;
	char	anti_c;
	int		i;

	n_quotes = 0;
	mini->end_string = begin;
	i = begin;
	while (line[i] != '\0' && line[i] != '\'' && line[i] != '"')
		i++;
	c = line[i];
	if (c == '\'')
		anti_c = '"';
	else
		anti_c = '\'';
	while (line[mini->end_string] != '\0')
	{
		if (line[mini->end_string] == c)
		{
			mini->i++;
			n_quotes++;
		}
		if ((line[mini->end_string] == ' ' || (line[mini->end_string] == anti_c
		&& command == 0)) && n_quotes % 2 == 0)
			break ;
		mini->end_string++;
	}
	return (fill_string(n_quotes, c, line, mini));
}
