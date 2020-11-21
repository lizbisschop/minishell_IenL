/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_utils_2.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 18:19:06 by iboeters      #+#    #+#                 */
/*   Updated: 2020/11/21 17:17:39 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ret_del(char *s, int i)
{
	if (s[i] == '>' && s[i + 1] == '>')
		i = i + 2;
	else
		i++;
	return (i);
}

void		set_open_q(char token, t_mini *mini)
{
	char	anti_q;
	char	temp;

	if (mini->q == '\'')
		anti_q = '"';
	else
		anti_q = '\'';
	if (token == mini->q)
		(mini->n_quotes)++;
	else if (token == anti_q && (mini->n_quotes) % 2 == 0)
	{
		mini->n_quotes++;
		temp = mini->q;
		mini->q = anti_q;
		anti_q = temp;
	}
}
