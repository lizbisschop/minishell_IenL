/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_pip_redir.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 18:16:25 by iboeters      #+#    #+#                 */
/*   Updated: 2020/11/09 18:16:27 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_redir_end(int *i, char *str, t_mini *mini)
{
	if (str[*i] == '>' || str[*i] == '<')
	{
		(*i)++;
		if (str[*i] == '>')
			(*i)++;
		while (is_whitespace(str[*i]) && str[*i] != '\0')
			(*i)++;
		if (str[*i] == '\0')
		{
			err("syntax error near unexpected token `newline'", "", 0, mini);
			return (-1);
		}
	}
	return (0);
}

int		check_semicolon(char *s, t_mini *mini, int *i)
{
	while (s[*i] != '\0')
	{
		skip_quoted(s, i);
		if (s[*i] == ';' && s[*i + 1] == ';')
		{
			err("syntax error near unexpected token `;;'", "", 0, mini);
			return (-1);
		}
		(*i)++;
	}
	return (0);
}

int		check_output_redir(char *s, t_mini *mini, int *i)
{
	char deli[4];

	if (s[*i] == '>' && s[*i + 1] == '>')
	{
		(*i)++;
		while (s[*i + 1] != '\0' && is_whitespace(s[*i + 1]))
			(*i)++;
		if (is_delimiter(s[*i + 1]) == 1)
		{
			deli[0] = '`';
			deli[1] = s[*i + 1];
			deli[2] = '\'';
			deli[3] = '\0';
			err("syntax error near unexpected token ", deli, 0, mini);
			return (-1);
		}
	}
	return (0);
}

int		check_delimiter(char *s, t_mini *mini, int *i)
{
	char	deli[4];
	char	delimiter;

	if (is_delimiter(s[*i]) || s[*i] == ';')
	{
		delimiter = s[*i];
		(*i)++;
		while (s[*i] != '\0' && is_whitespace(s[*i]))
			(*i)++;
		if ((is_delimiter(s[*i]) == 1 || s[*i] == ';')
		&& (delimiter != '|' || s[*i] == '|'))
		{
			deli[0] = '`';
			deli[1] = s[*i];
			deli[2] = '\'';
			deli[3] = '\0';
			err("syntax error near unexpected token ", deli, 0, mini);
			return (-1);
		}
	}
	return (0);
}

int		check_pip_redir(int *i, char *s, t_mini *mini)
{
	int		old_i;

	old_i = *i;
	if (check_redir_end(i, s, mini) == -1)
		return (-1);
	*i = old_i;
	if (check_semicolon(s, mini, i) == -1)
		return (-1);
	*i = old_i;
	if (s[*i] == '>' && s[*i + 1] == '>' && s[*i + 2] == '>')
	{
		if (s[*i + 3] == '>')
			err("syntax error near unexpected token `>>'", "", 0, mini);
		else
			err("syntax error near unexpected token `>'", "", 0, mini);
		return (-1);
	}
	if (check_output_redir(s, mini, i) == -1)
		return (-1);
	if (check_delimiter(s, mini, i) == -1)
		return (-1);
	return (0);
}
