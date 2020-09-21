/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quotes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/17 16:04:20 by iboeters      #+#    #+#                 */
/*   Updated: 2020/09/21 14:54:06 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		multi_lines(char *str, char c)
{
	int i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
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

char	*unquote(char c, char *line, t_mini *mini)
{
	int		n_quotes;

	n_quotes = 0;
	mini->end_string = mini->i;
	while (line[mini->end_string] != '\0')
	{
		if (line[mini->end_string] == c)
		{
			mini->i++;
			n_quotes++;
		}
		if (line[mini->end_string] == ' ' && n_quotes % 2 == 0)
			break ;
		mini->end_string++;
	}
	return (fill_string(n_quotes, c, line, mini));
}

int		quotes(t_mini *mini, char c, char *line)
{
	if (multi_lines(line, c))
	{
		ft_putstr_fd("Error:\nMultiline command.\n", 1);
		return (-1);
	}
	mini->command = unquote(c, line, mini);
	printf("command=|%s|\n", mini->command);
	return (0);
}
