/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_substr.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 18:17:58 by iboeters      #+#    #+#                 */
/*   Updated: 2020/11/09 18:17:59 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_quotes(char *s, t_mini *mini)
{
	if (s[mini->end] == '"')
	{
		mini->end++;
		while (s[mini->end] != '"' && s[mini->end] != '\0')
			mini->end++;
	}
	else if (s[mini->end] == '\'')
	{
		mini->end++;
		while (s[mini->end] != '\'' && s[mini->end] != '\0')
			mini->end++;
	}
}

int		find_substr(char *s, t_mini *mini)
{
	int	empty;

	empty = 1;
	while (s[mini->end] != '\0')
	{
		if (empty == 1 && (!((s[mini->end] >= 9
		&& s[mini->end] <= 12) || s[mini->end] == 32
		|| s[mini->end] == ';') || (s[mini->end]
		== '\\' && s[mini->end + 1] == '\\')))
			empty = 0;
		check_quotes(s, mini);
		if (s[mini->end] == '\\' && s[mini->end + 1] != '\0')
		{
			empty = 0;
			mini->end++;
		}
		else if (s[mini->end] == ';' && empty == 0)
			return (1);
		else if (s[mini->end] == ';' && empty == 1)
			return (0);
		mini->end++;
	}
	if (empty == 1)
		return (0);
	return (1);
}
