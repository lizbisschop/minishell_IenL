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

int		check_pip_redir(int *i, char *s, t_mini *mini)
{
	char deli[4];
	int	old_i;
	char delimiter;

	old_i = *i;
	if (check_redir_end(i, s, mini) == -1)
		return (-1);
	*i = old_i;
	while (s[*i] != '\0')
	{
		if (s[*i] == ';' && s[*i + 1] == ';')
		{
			err("syntax error near unexpected token `;;'", "", 0, mini);
			return (-1);
		}
		(*i)++;
	}
	*i = old_i;
	if (s[*i] == '>' && s[*i + 1] == '>' && s[*i + 2] == '>')
	{
		if (s[*i + 3] == '>')
			err("syntax error near unexpected token `>>'", "", 0, mini);
		else
			err("syntax error near unexpected token `>'", "", 0, mini);
		return (-1);
	}
	else if (s[*i] == '>' && s[*i + 1] == '>')
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
	if (is_delimiter(s[*i]) || s[*i] == ';')
	{
		delimiter = s[*i];
		(*i)++;
		while (s[*i] != '\0' && is_whitespace(s[*i]))
			(*i)++;
		if ((is_delimiter(s[*i]) == 1 || s[*i] == ';') && (delimiter != '|' || s[*i] == '|'))
		{
			deli[0] = '`';
			deli[1] = s[*i];
			deli[2] = '\'';
			deli[3] = '\0';
			err("syntax error near unexpected token ", deli, 0, mini);
			return (-1);
		}
	}
	// if (s[*i] == '|')
	// {
	// 	while (is_whitespace())
	// 	err("syntax error near unexpected token `|'", "", 0, mini);
	// 	return (-1);
	// }
	// else if (s[*i] == '<' && s[*i + 1] == '<')
	// {
	// 	err("syntax error near unexpected token `<'", "", 0, mini);
	// 	return (-1);
	// }
	// else if (s[*i] == '>' && s[*i + 1] == '<')
	// {
	// 	err("syntax error near unexpected token `<'", "", 0, mini);
	// 	return (-1);
	// }
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
		skip_quoted(s, &i);
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
