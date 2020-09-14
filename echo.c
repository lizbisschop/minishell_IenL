/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: liz <liz@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 14:31:44 by liz           #+#    #+#                 */
/*   Updated: 2020/09/14 17:29:19 by liz           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		n_flag(char *str, int *i)
{
	if (str[*i] == '-' && str[*i + 1] == 'n' && str[*i + 2] == ' ')
	{
		*i += 3;
		return (1);
	}
	return (0);
}

void	echo(char *str)
{
	int i;
	int	flag;
	int space;

	i = 0;
	skipping_spaces(str, &i);
	flag = n_flag(&str[i], &i);
	skipping_spaces(str, &i);
	while (str[i] != '\0')
	{
		space = 0;
		if (str[i] == ' ')
			space = 1;
		skipping_spaces(str, &i);
		if (str[i] == '"')
		{
			i++;
			if (space == 1)
				ft_putchar_fd(' ', 1);
			while (str[i] != '"' && str[i] != '\0')
			{
				ft_putchar_fd(str[i], 1);
				i++;
			}
			i++;
		}
		else if (ft_isascii(str[i]) && str[i] != '\0')
		{
			if (space == 1)
				ft_putchar_fd(' ', 1);
			while (str[i] != '\0' && str[i] != ' ')
			{
				ft_putchar_fd(str[i], 1);
				i++;
			}
		}
		else
			i++;
	}
	if (!flag)
		ft_putchar_fd('\n', 1);
}
