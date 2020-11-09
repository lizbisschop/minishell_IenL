/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_commands.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 18:18:49 by iboeters      #+#    #+#                 */
/*   Updated: 2020/11/09 18:18:50 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
