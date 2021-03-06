/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_for_errors.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 18:16:19 by iboeters      #+#    #+#                 */
/*   Updated: 2020/11/23 13:34:40 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_pipes_redirect_2(char *s, t_mini *mini, int *i)
{
	while (s[*i] != '\0')
	{
		if (s[*i] == '\\' && s[*i + 1] != '\0')
			(*i) += 2;
		else if (s[*i] == '\\' && s[*i + 1] == '\0')
			(*i)++;
		skip_quoted(s, i);
		if (check_pip_redir(i, s, mini) == -1)
			return (-1);
		(*i)++;
	}
	return (0);
}

int		check_pipes_redirect(char *s, t_mini *mini)
{
	int i;

	i = 0;
	while ((is_whitespace(s[i]) && s[i] != '\0') || s[i] == ';')
	{
		if (s[i] == '\\' && s[i + 1] != '\0')
			i += 2;
		else if (s[i] == '\\' && s[i + 1] == '\0')
			i++;
		skip_quoted(s, &i);
		if (s[i] == ';')
		{
			err("syntax error near unexpected token `;'", "", 0, mini);
			mini->exit_int = 258;
			return (-1);
		}
		i++;
	}
	if (check_pipes_redirect_2(s, mini, &i) == -1)
		return (-1);
	return (0);
}

int		loop_for_err(char *s, t_mini *mini)
{
	int i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\\' && s[i + 1] != '\0')
			i += 2;
		else if (s[i] == '\\' && s[i + 1] == '\0')
			i++;
		if (s[i] == '\\' && s[i + 1] == '\0')
		{
			err("multiline command", "", 0, mini);
			return (-1);
		}
		i++;
	}
	return (0);
}

int		check_for_errors(char *s, t_mini *mini)
{
	if (multi_lines(s))
	{
		err("multiline command", "", 0, mini);
		return (-1);
	}
	if (check_pipes_redirect(s, mini) == -1)
		return (-1);
	return (loop_for_err(s, mini));
}
