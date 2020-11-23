/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_utils_2.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 18:19:06 by iboeters      #+#    #+#                 */
/*   Updated: 2020/11/23 13:47:22 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void		malloc_error(void)
{
	ft_putstr_fd("bash: malloc fail\n", 2);
	exit(1);
}

int			check_semicolon(char *s, t_mini *mini, int *i)
{
	while (s[*i] != '\0')
	{
		skip_quoted(s, i);
		if (s[*i] == ';' && s[*i + 1] == ';')
		{
			err("syntax error near unexpected token `;;'", "", 0, mini);
			mini->exit_int = 258;
			return (-1);
		}
		(*i)++;
	}
	return (0);
}

void		switch_quotes(t_mini *mini, char *q, char *anti_q)
{
	char	temp;

	mini->n_quotes++;
	temp = *q;
	*q = *anti_q;
	*anti_q = temp;
}
