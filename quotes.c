/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quotes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/17 16:04:20 by iboeters      #+#    #+#                 */
/*   Updated: 2020/09/17 16:59:26 by iboeters      ########   odam.nl         */
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

char	*get_command(char c, char *line, t_mini *mini)
{
	int		i;
	int		j;
	int		n_quotes;
	char	*str;

	i = mini->i;
	j = 0;
	n_quotes = 0;
	mini->end_command = mini->i;
	printf("%s\n", line);
	while (line[mini->end_command] != '\0')
	{
		if (line[mini->end_command] == c)
			n_quotes++;
		if (line[mini->end_command] == ' ' && n_quotes % 2 == 0)
			break ;
		mini->end_command++;
	}
	str = (char *)malloc((mini->end_command - n_quotes + 1) * sizeof(char));
	printf("%i\n", mini->end_command);
	while (i < mini->end_command)
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

int		quotes(t_mini *mini, char c, char *line)
{
	printf("aangeroepen!\n");
	if (multi_lines(line, c))
	{
		ft_putstr_fd("Error:\nMultiline command.\n", 1);
		return (1);
	}
	mini->command = get_command(c, line, mini);
	printf("command=|%s|\n", mini->command);
	return (0);
}
