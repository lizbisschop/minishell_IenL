/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 18:16:31 by iboeters      #+#    #+#                 */
/*   Updated: 2020/11/21 17:10:45 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		set_n_flag(int *n_flag, int *i, char **tokens, int tok_amount)
{
	int		j;

	*n_flag = 0;
	while (*i < tok_amount && ft_strncmp("-n", tokens[*i], 2) == 0)
	{
		j = 2;
		while (tokens[*i][j] == 'n')
			j++;
		if (tokens[*i][j] != '\0')
			break ;
		*n_flag = 1;
		(*i)++;
	}
}

void		echo(char **tokens, int tok_amount, t_mini *mini)
{
	int		i;
	int		n_flag;

	i = 1;
	n_flag = 0;
	if (tok_amount > 1)
	{
		set_n_flag(&n_flag, &i, tokens, tok_amount);
		while (i < tok_amount)
		{
			ft_putstr_fd(tokens[i], 1);
			if (i < tok_amount - 1 && tokens[i] != NULL)
			{
				ft_putchar_fd(' ', 1);
			}
			i++;
		}
	}
	if (!n_flag)
		ft_putchar_fd('\n', 1);
	mini->exit_int = 0;
}
