/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_pip_redir.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 18:16:25 by iboeters      #+#    #+#                 */
/*   Updated: 2020/11/23 12:59:10 by iboeters      ########   odam.nl         */
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
			mini->exit_int = 258;
			return (-1);
		}
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
			mini->exit_int = 258;
			return (-1);
		}
	}
	return (0);
}

int		piped_deli(t_mini *mini, char *s, int *i, char delimiter)
{
	char deli[4];

	if (delimiter == '|' && (is_delimiter(s[*i]) == 1 || s[*i] == ';'))
	{
		deli[0] = '`';
		deli[1] = s[*i];
		deli[2] = '\'';
		deli[3] = '\0';
		(*i)++;
		while (s[*i] != '\0' && is_whitespace(s[*i]))
			(*i)++;
		if (s[*i] == '\0' || is_delimiter(s[*i]))
		{
			err("syntax error near unexpected token ", deli, 0, mini);
			mini->exit_int = 258;
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
			mini->exit_int = 258;
			return (-1);
		}
		else if (piped_deli(mini, s, i, delimiter) == -1)
			return (-1);
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
		mini->exit_int = 258;
		return (-1);
	}
	if (check_output_redir(s, mini, i) == -1)
		return (-1);
	if (check_delimiter(s, mini, i) == -1)
		return (-1);
	return (0);
}
