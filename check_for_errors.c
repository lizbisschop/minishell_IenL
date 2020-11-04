#include "minishell.h"

int		check_quotes(int *i, char *s)
{
	if (s[*i] == '\'')
	{
		*i++;
		while (s[*i] != '\0' && s[*i] != '\'')
			*i++;
		if (s[*i] == '\'')
			*i++;
	}
	if (s[*i] == '\"')
	{
		*i++;
		while (s[*i] != '\0' && s[*i] != '\"')
			*i++;
		if (s[*i] == '\"')
			*i++;
	}
}

int		check_pip_redir(int *i, char *s, t_mini *mini)
{
	if (s[*i] == '|' && s[*i + 1] == '|')
	{
		err("syntax error near unexpected token `|'", "", 0, mini);
		return (-1);
	}
	else if (s[*i] == '<' && s[*i + 1] == '<')
	{
		err("syntax error near unexpected token `<'", "", 0, mini);
		return (-1);
	}
	else if (s[*i] == '>' && s[*i + 1] == '>' && s[*i + 2] == '>')
	{
		if (s[*i + 3] == '>')
			err("syntax error near unexpected token `>>'", "", 0, mini);
		else
			err("syntax error near unexpected token `>'", "", 0, mini);
		return (-1);
	}
	else if (s[*i] == '>' && s[*i + 1] == '<')
	{
		err("syntax error near unexpected token `<'", "", 0, mini);
		return (-1);
	}
	return (0);
}

int		check_pipes_redirect(char *s, t_mini *mini)
{
	int i;

	i = 0;
	while ((is_whitespace(s[i]) && s[i] != '\0') || s[i] == ';')
	{
		if (s[i] == ';')
		{
			err("syntax error near unexpected token `;'", "", 0, mini);
			return (-1);
		}
		i++;
	}
	while (s[i] != '\0')
	{
		check_quotes(&i, s);
		if (check_pip_redir(&i, s, mini) == -1)
			return (-1);
		i++;
	}
	return (0);
}

int		loop_for_err(char *s, t_mini *mini)
{
	int i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\\' && s[i + 1] != '\0')
		{
			i++;
		}
		else if (s[i] == '\\' && s[i + 1] == '\0')
		{
			err("multiline command", "", 0, mini);
			return (-1);
		}
		else if (s[i] == ';' && s[i + 1] == ';')
		{
			err("syntax error near unexpected token `;;'", "", 0, mini);
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
