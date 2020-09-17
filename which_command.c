/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   which_command.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: liz <liz@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 14:20:20 by liz           #+#    #+#                 */
/*   Updated: 2020/09/17 14:27:07 by liz           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_command(char *input, t_mini *mini)
{
	while (input[mini->i] != ';' && input[mini->i] != '\0')
		mini->i++;
	mini->i++;
}

int 	find_command(char *input, t_mini *mini)
{
	// printf("find command\n");
	if (ft_strncmp("echo ", &input[mini->i], 5) == 0)
	{
		mini->i += 5;
		// printf(" echo found\n");
		return (1);
	}
	else if (ft_strncmp("pwd", &input[mini->i], 3) == 0)
	{
		mini->i += 3;
		return (2);
	}
	else if (ft_strncmp("exit", &input[mini->i], 4) == 0)
		exit(0);
	else if (ft_strncmp("cd ", &input[mini->i], 3) == 0)
	{	
		mini-> i += 3;
		return (3);
	}
	return (0);
}

void 	skip_whitespaces(char *str, t_mini *mini)
{
	
	// printf("c%c\n", str[*count]);
	while (str[mini->i] != '\0' && ((str[mini->i] >= 9 && str[mini->i] <= 12)
	|| str[mini->i] == 32))
	{
		mini->i++;
	}
}

void 	which_command(t_mini *mini)
{
	int j;
	int cmd;

	j = 0;
	while (j <= mini->cmds)
	{
		cmd = 0;
		// printf("yes\n");
		skip_whitespaces(mini->sp_input[j], mini);
		cmd = find_command(mini->sp_input[j], mini);
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
