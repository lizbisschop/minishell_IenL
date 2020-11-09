/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 18:19:09 by iboeters      #+#    #+#                 */
/*   Updated: 2020/11/09 18:19:10 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_tok_end(char *s, int *i)
{
	if (s[*i] == '\'' || s[*i] == '"')
	{
		skip_quoted(s, i);
		if (is_delimiter(s[*i]))
			return (1);
	}
	else if (is_delimiter(s[*i]))
	{
		*i = (s[*i] == '>' && s[*i + 1] == '>') ? *i + 2 : *i + 1;
		return (1);
	}
	else if (ft_isascii(s[*i]))
	{
		while (s[*i] != '\0' && s[*i] != '\'' && s[*i] != '"' &&
		!is_delimiter(s[*i]) && !is_whitespace(s[*i]) && ft_isascii(s[*i]))
			(*i)++;
		if (s[*i] != '\'' && s[*i] != '"')
			return (1);
	}
	else
		(*i)++;
	return (0);
}

int		token_amount(char *s, t_mini *mini)
{
	int		i;
	int		tok_n;

	i = 0;
	tok_n = 0;
	while (s[i] != '\0')
	{
		skip_wspaces(s, &i);
		if (s[i] == '\0')
			break ;
		while (s[i] != '\0')
		{
			if (check_tok_end(s, &i) == 1)
				break ;
		}
		tok_n++;
	}
	return (tok_n);
}

int		tok_end(char *s, int i)
{
	while (s[i] != '\0')
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			skip_quoted(s, &i);
			if (is_delimiter(s[i]))
				return (i);
		}
		else if (is_delimiter(s[i]))
			return (ret_del(s, i));
		else if (ft_isascii(s[i]))
		{
			while (s[i] != '\0' && ft_isascii(s[i]) && s[i] != '\'' &&
			s[i] != '"' && !is_delimiter(s[i]) && !is_whitespace(s[i]))
				i++;
			if (s[i] != '\'' && s[i] != '"')
				return (i);
		}
		else
			i++;
	}
	return (i);
}

void	create_tokens(int cmd, t_mini *mini)
{
	int		i;
	int		j;
	int		end;

	i = 0;
	j = 0;
	mini->c[cmd].tok_amount = token_amount(mini->sp_input[cmd], mini);
	mini->c[cmd].tokens = (char **)malloc(sizeof(char *) *
	(mini->c[cmd].tok_amount + 1));
	if (!(mini->c[cmd].tokens))
	{
		ft_putstr_fd("bash: Malloc fail\n", 2);
		exit(1);
	}
	while (j < mini->c[cmd].tok_amount)
	{
		skip_wspaces(mini->sp_input[cmd], &i);
		end = tok_end(mini->sp_input[cmd], i);
		mini->c[cmd].tokens[j] = ft_substr(mini->sp_input[cmd], i, end - i);
		i = end;
		j++;
	}
	mini->c[cmd].tokens[j] = NULL;
}

int		tokens(t_mini *mini)
{
	int		end;
	int		cmd;

	cmd = 0;
	mini->c = (t_command *)malloc(sizeof(t_command) * (mini->cmds + 1));
	if (mini->c == (void*)-1)
	{
		ft_putstr_fd("bash: Malloc fail\n", 2);
		exit(1);
	}
	while (cmd < mini->cmds)
	{
		create_tokens(cmd, mini);
		cmd++;
	}
	return (0);
}
