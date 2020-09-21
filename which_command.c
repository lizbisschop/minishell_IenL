/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   which_command.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: liz <liz@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 14:20:20 by liz           #+#    #+#                 */
/*   Updated: 2020/09/21 14:59:03 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_command(char *input, t_mini *mini)
{
	while (input[mini->i] != ';' && input[mini->i] != '\0')
		mini->i++;
	mini->i++;
}

int		find_command(t_mini *mini)
{
	if (ft_strncmp("echo", mini->command, 4) == 0 &&
	ft_strlen(mini->command) == 4)
	{
		mini->i += 4;
		return (1);
	}
	else if (ft_strncmp("pwd", mini->command, 3) == 0 &&
	ft_strlen(mini->command) == 3)
	{
		mini->i += 3;
		return (2);
	}
	else if (ft_strncmp("exit", mini->command, 4) == 0 &&
	ft_strlen(mini->command) == 4)
		exit(0);
	else if (ft_strncmp("cd", mini->command, 3) == 0 &&
	ft_strlen(mini->command) == 2)
	{
		mini->i += 3;
		return (3);
	}
	return (0);
}

void	skip_whitespaces(char *str, t_mini *mini)
{
	while (str[mini->i] != '\0' && ((str[mini->i] >= 9 && str[mini->i] <= 12)
	|| str[mini->i] == 32))
	{
		mini->i++;
	}
}

void	which_command(t_mini *mini)
{
	int j;
	int cmd;

	j = 0;
	while (j <= mini->cmds)
	{
		cmd = 0;
		skip_whitespaces(mini->sp_input[j], mini);
		if (quotes(mini, '"', mini->sp_input[j]) == -1)
			return ;
		cmd = find_command(mini);
		if (cmd == 1)
		{
			echo(mini->sp_input[j], mini);
		}
		else if (cmd == 2)
		{
			pwd();
		}
		else if (cmd == 0)
		{
			ft_putstr_fd("Error:\nCommand not found.\n", 1);
			skip_command(mini->sp_input[j], mini);
		}
		else if (cmd == 3)
		{
			cd(mini->sp_input[j], mini);
		}
		j++;
		mini->i = 0;
	}
}
