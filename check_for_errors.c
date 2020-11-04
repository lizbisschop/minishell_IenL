#include "minishell.h"

void	error_multi_line_pipe(int i, int cmd, t_command command, t_mini *mini)
{
	if (command.tokens[i][0] == '|' && i == 0)
		err("syntax error near unexpected token `|'", "", 0, mini);
	else if (i == command.tok_amount - 1)
	{
		if (cmd == mini->cmds - 1)
			err("multiline command", "", 0, mini);
		else
			err("syntax error near unexpected token `;'", "", 0, mini);
	}
	else
		err("syntax error near unexpected token `|'", "", 0, mini);
}

int		multi_line_pipe(t_mini *mini)
{
	int		cmd;
	int		i;

	cmd = 0;
	i = 0;
	while (cmd < mini->cmds)
	{
		while (i < mini->c[cmd].tok_amount)
		{
			if (ft_strncmp(mini->c[cmd].tokens[i], "|", 1) == 0
			&& ft_strlen(mini->c[cmd].tokens[i]) == 1 && (i == 0 ||
			i == mini->c[cmd].tok_amount - 1))
			{
				error_multi_line_pipe(i, cmd, mini->c[cmd], mini);
				return (-1);
			}
			i++;
		}
		cmd++;
	}
	return (0);
}

int		multi_lines(char *str)
{
	int		double_q;
	int		single_q;
	int		i;

	double_q = 0;
	single_q = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\\' && str[i + 1] != '\'' && str[i + 1] != '\0')
			i++;
		else if (str[i] == '\'' && (double_q % 2) == 0)
			single_q++;
		else if (str[i] == '"' && (single_q % 2) == 0)
			double_q++;
		i++;
	}
	if ((single_q % 2) == 1 || (double_q % 2) == 1)
		return (1);
	return (0);
}

int 	check_pipes_redirect(char *s, t_mini *mini)
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
		if (s[i] == '\'')
		{
			i++;
			while (s[i] != '\0' && s[i] != '\'')
				i++;
			if (s[i] == '\'')
				i++;
		}
		if (s[i] == '\"')
		{
			i++;
			while (s[i] != '\0' && s[i] != '\"')
				i++;
			if (s[i] == '\"')
				i++;
		}
		if (s[i] == '|' && s[i + 1] == '|')
		{
			err("syntax error near unexpected token `|'", "", 0, mini);
			return (-1);
		}
		else if (s[i] == '<' && s[i + 1] == '<')
		{
			err("syntax error near unexpected token `<'", "", 0, mini);
			return (-1);
		}
		else if (s[i] == '>' && s[i + 1] == '>' && s[i + 2] == '>')
		{
			if (s[i + 3] == '>')
				err("syntax error near unexpected token `>>'", "", 0, mini);
			else
				err("syntax error near unexpected token `>'", "", 0, mini);
			return (-1);
		}
		i++;
	}
	return (0);
}

int check_for_errors(char *s, t_mini *mini)
{
	int i;

	i = 0;
	if (multi_lines(s))
	{
		err("multiline command", "", 0, mini);
		return (-1);
	}
	if (check_pipes_redirect(s, mini) == -1)
		return (-1);
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
