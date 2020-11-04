#include "minishell.h"

void	skip_quoted(char *s, int *i)
{
	if (s[*i] == '\'')
	{
		(*i)++;
		while (s[*i] != '\0' && s[*i] != '\'')
			(*i)++;
		if (s[*i] == '\'')
			(*i)++;
	}
	else if (s[*i] == '"')
	{
		(*i)++;
		while (s[*i] != '\0' && s[*i] != '"')
			(*i)++;
		if (s[*i] == '"')
			(*i)++;
	}
}

int		token_amount(char *s)
{
	int		i;
	int		tokens;
	i = 0;
	tokens = 0;
	while (s[i] != '\0')
	{
		skip_wspaces(s, &i);
		if (s[i] == '\0')
			break ;
		while (s[i] != '\0')
		{
			if (s[i] == '\'' || s[i] == '"')
				skip_quoted(s, &i);
			else if (is_delimiter(s[i]))
			{
				if (s[i] == '>' && s[i + 1] == '>')
					i = i + 2;
				else
					i++;
				break ;
			}
			else if (ft_isascii(s[i]))
			{
				while (s[i] != '\0' && s[i] != '\'' && s[i] != '"' &&
				!is_delimiter(s[i]) && !is_whitespace(s[i]) && ft_isascii(s[i]))
					i++;
				if (s[i] != '\'' && s[i] != '"')
					break ;
			}
			else
				i++;
		}
		tokens++;
	}
	return (tokens);
}

int		tok_end(char *s, int i)
{
	while (s[i] != '\0')
	{
		if (s[i] == '\'' || s[i] == '"')
			skip_quoted(s, &i);
		else if (is_delimiter(s[i]))
		{
			if (s[i] == '>' && s[i + 1] == '>')
				i = i + 2;
			else
				i++;
			return (i);
		}
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
	mini->c[cmd].tok_amount = token_amount(mini->sp_input[cmd]);
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
		printf("[%s]\n", mini->c[cmd].tokens[j]); //weg halen voor eval
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
