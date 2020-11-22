/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_commands.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 18:18:49 by iboeters      #+#    #+#                 */
/*   Updated: 2020/11/22 20:26:33 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_quotes(char *s, t_mini *mini)
{
	if (s[mini->end] == '"')
	{
		mini->end++;
		while (s[mini->end] != '"' && s[mini->end] != '\0')
		{
			if (s[mini->end] == '\\' && s[mini->end + 1] != '\0')
				mini->end++;
			mini->end++;
		}
		if (s[mini->end] == '"')
			mini->end++;
	}
	else if (s[mini->end] == '\'')
	{
		mini->end++;
		while (s[mini->end] != '\'' && s[mini->end] != '\0')
		{
			mini->end++;
		}
		if (s[mini->end] == '\'')
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

int		find_start_end(t_mini *mini, int *i, char *s, int command)
{
	int ret;

	ret = 0;
	while (ret == 0)
	{
		ret = find_substr(s, mini);
		if (ret == 1)
		{
			mini->sp_input[command] = ft_substr(s, *i, mini->end - *i);
			if (!mini->sp_input[command])
			{
				err("malloc has failed", "", 0, mini);
				return (-1);
			}
		}
		mini->end++;
		*i = mini->end;
	}
	return (0);
}

int		save_commands(t_mini *mini, char *s)
{
	int command;
	int i;
	int ret;

	command = 0;
	i = 0;
	while (command < mini->cmds)
	{
		if (find_start_end(mini, &i, s, command) == -1)
			return (-1);
		i = mini->end;
		command++;
	}
	mini->sp_input[command] = NULL;
	return (0);
}
