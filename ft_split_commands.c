/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split_commands.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 18:18:05 by iboeters      #+#    #+#                 */
/*   Updated: 2020/11/23 10:08:20 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	count_semicolon(char *s, int *i, int *empty, int *semicolon)
{
	if (s[*i] == '\\' && s[*i + 1] != '\0')
	{
		*empty = 0;
		(*i)++;
	}
	else if (s[*i] == ';' && *empty == 0)
	{
		(*semicolon)++;
		*empty = 1;
	}
}

int		command_count(char *s)
{
	int i;
	int semicolon;
	int	empty;

	i = 0;
	semicolon = 0;
	empty = 1;
	while (s[i] != '\0')
	{
		if (empty == 1 && (!((s[i] >= 9 && s[i] <= 12) || s[i] == 32
		|| s[i] == ';') || (s[i] == '\\' &&
		s[i + 1] == '\\')))
			empty = 0;
		skip_quoted(s, &i);
		count_semicolon(s, &i, &empty, &semicolon);
		if (s[i] != '\0')
			i++;
	}
	if (empty == 1)
		semicolon--;
	return (semicolon + 1);
}

int		ft_split_commands(char *s, t_mini *mini)
{
	mini->cmds = command_count(s);
	mini->sp_input = (char **)malloc(sizeof(char *) * (mini->cmds + 1));
	mini->sp_input[mini->cmds] = NULL;
	if (!mini->sp_input)
		malloc_error();
	if (check_for_errors(s, mini) == -1)
	{
		if (mini->sp_input)
			free(mini->sp_input);
		return (-1);
	}
	if (save_commands(mini, s) == -1)
		return (-1);
	return (0);
}
