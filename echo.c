/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: liz <liz@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 14:31:44 by liz           #+#    #+#                 */
/*   Updated: 2020/09/17 16:23:00 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		n_flag(char *str, t_mini *mini)
{
	if (ft_strncmp("-n ", &str[mini->i], 3) == 0)
	{
		mini->i += 3;
		return (1);
	}
	return (0);
}

void	echo(char *str, t_mini *mini)
{
	int	flag;
	int space;

	skip_whitespaces(str, mini);
	flag = n_flag(str, mini);
	skip_whitespaces(str, mini);
	while (str[mini->i] != '\0')
	{
		// printf("string is:%s\n", &str[mini->i]);
		space = 0;
		if (str[mini->i] == ' ')
			space = 1;
		skip_whitespaces(str, mini);
		if (str[mini->i] == '"')
		{
			mini->i++;
			if (space == 1)
				ft_putchar_fd(' ', 1);
			while (str[mini->i] != '"' && str[mini->i] != '\0')
			{
				ft_putchar_fd(str[mini->i], 1);
				mini->i++;
			}
			mini->i++;
		}
		if (ft_isascii(str[mini->i]) && str[mini->i] != '\0')
		{
			// printf("0000\n");
			if (space == 1)
				ft_putchar_fd(' ', 1);
			while (str[mini->i] != '\0' && str[mini->i] != ' ')
			{
				ft_putchar_fd(str[mini->i], 1);
				mini->i++;
			}
		}
		else
			mini->i++;
	}
	if (!flag)
		ft_putchar_fd('\n', 1);
}
