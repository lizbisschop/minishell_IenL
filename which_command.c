/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   which_command.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: liz <liz@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 14:20:20 by liz           #+#    #+#                 */
/*   Updated: 2020/09/22 11:54:36 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_command(char *input, t_mini *mini)
{
	while (input[mini->i] != ';' && input[mini->i] != '\0')
		mini->i++;
	mini->i++;
}

int		find_command(t_mini *mini, int j, char **envp)
{
	if (ft_strncmp("echo", mini->command, 4) == 0 &&
	ft_strlen(mini->command) == 4)
	{
		mini->i += 4;
		echo(mini->sp_input[j], mini);
	}
	else if (ft_strncmp("pwd", mini->command, 3) == 0 &&
	ft_strlen(mini->command) == 3)
	{
		mini->i += 3;
		pwd();
	}
	else if (ft_strncmp("exit", mini->command, 4) == 0 &&
	ft_strlen(mini->command) == 4)
		exit(0);
	else if (ft_strncmp("cd", mini->command, 2) == 0 &&
	ft_strlen(mini->command) == 2)
	{
		mini->i += 2;
		cd(mini->sp_input[j], mini, envp);
	}
	else if (ft_strncmp("env", mini->command, 3) == 0 &&
	ft_strlen(mini->command) == 3)
	{
		mini->i +=3;
		env_command(envp);
	}
	else
	{
		ft_putstr_fd("Error:\nCommand: ", 1);
		ft_putstr_fd(mini->command, 1);
		ft_putstr_fd(" not found.\n", 1);
		skip_command(mini->sp_input[j], mini);
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

int		get_command(t_mini *mini, char *line)
{
	if (multi_lines(line))
	{
		ft_putstr_fd("Error:\nMultiline command.\n", 1);
		return (-1);
	}
	mini->command = unquote(&line[mini->i], mini, 1);
	// printf("command=|%s|\n", mini->command);
	return (0);
}

void	which_command(t_mini *mini, char **envp)
{
	int j;

	j = 0;
	while (j <= mini->cmds)
	{
		skip_whitespaces(mini->sp_input[j], mini);
		if (get_command(mini, mini->sp_input[j]) == -1)
			return ;
		find_command(mini, j, envp);
		j++;
		mini->i = 0;
		if (mini->command)
		{
			free(mini->command);
			mini->command = NULL;
		}
	}
}
