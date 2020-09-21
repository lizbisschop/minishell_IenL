/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: liz <liz@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 14:31:44 by liz           #+#    #+#                 */
/*   Updated: 2020/09/21 18:47:14 by iboeters      ########   odam.nl         */
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
	int		flag;
	int		space;
	char	*word;
	int		i;

	i = 0;
	skip_whitespaces(str, mini);
	flag = n_flag(str, mini);
	skip_whitespaces(str, mini);
	word = ft_strdup("");
	while (str[mini->i] != '\0')
	{
		// printf("string is:%s\n", &str[mini->i]);
		space = 0;
		i = 0;
		if (str[mini->i] == ' ')
			space = 1;
		skip_whitespaces(str, mini);
		if (str[mini->i] == '"' || str[mini->i] == '\'')
		{
			word = unquote(&str[mini->i], mini, i, 0);
			if (space == 1)
				ft_putchar_fd(' ', 1);
			while (word[i] != '\0')
			{
				ft_putchar_fd(word[i], 1);
				mini->i++;
				i++;
			}
		}
		else if (ft_isascii(str[mini->i]) && str[mini->i] != '\0')
		{
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
		if (word)
		{
			free(word);
			word = NULL;
		}
	}
	if (!flag)
		ft_putchar_fd('\n', 1);
}
