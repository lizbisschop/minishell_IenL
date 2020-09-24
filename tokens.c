#include "minishell.h"

int		is_delimiter(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int		is_whitespace(char c)
{
	if ((c >= 9 && c <= 12) || c == 32)
		return (1);
	return (0);
}

void	skip_wspaces(char *s, int *i)
{
	while (s[*i] != '\0' && ((s[*i] >= 9 && s[*i] <= 12)
	|| s[*i] == 32))
	{
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
			if (is_delimiter(s[i]))
			{
				printf("break1%s\n", &s[i]);
				if (s[i] == '>' && s[i + 1] == '>')
					i = i + 2;
				else
					i++;
				break ;
			}
			else if (s[i] == '\'')
			{
				i++;
				while (s[i] != '\0' && s[i] != '\'')
					i++;
				if (s[i] == '\'')
					i++;
			}
			else if (s[i] == '"')
			{
				i++;
				while (s[i] != '\0' && s[i] != '"')
					i++;
				if (s[i] == '"')
					i++;
			}
			else if (ft_isascii(s[i]))
			{
				while (s[i] != '\0' && !is_delimiter(s[i]) && !is_whitespace(s[i]) && ft_isascii(s[i]))
					i++;
				printf("break2%s\n", &s[i]);
				break ;
			}
			else
				i++;
		}
		tokens++;
	}
	return (tokens);
}

int		find_end(char *s, int i)
{
	while (s[i] != '\0')
	{
		if (is_delimiter(s[i]))
		{
			// printf("end_found1%s\n", &s[i]);
			if (s[i] == '>' && s[i + 1] == '>')
				i = i + 2;
			else
				i++;
			return (i);
		}
		else if (s[i] == '\'')
		{
			i++;
			while (s[i] != '\0' && s[i] != '\'')
				i++;
			if (s[i] == '\'')
				i++;
		}
		else if (s[i] == '"')
		{
			i++;
			while (s[i] != '\0' && s[i] != '"')
				i++;
			if (s[i] == '"')
				i++;
		}
		else if (ft_isascii(s[i]))
		{
			while (s[i] != '\0' && !is_delimiter(s[i]) && !is_whitespace(s[i]) && ft_isascii(s[i]))
				i++;
			// printf("end_found2%s\n", &s[i]);
			return (i);
		}
		else
			i++;
	}
	return (0);
}

int		tokens(t_mini *mini)
{
	int		end;
	int		i;
	int		j;
	int		tokens;
	int		cmd;
	char	*s;

	i = 0;
	j = 0;
	cmd = 0;
	mini->c = malloc(sizeof(t_command) * mini->cmds + 1);
	// if (mini->c == -1)
	// {
	// 	printf("Malloc fail\n");
	// 	exit(0);
	// }
	// printf("[%s][%i]\n", s, tokens);
	while (cmd < mini->cmds)
	{
		s = mini->sp_input[cmd];
		tokens = token_amount(s);
		printf("string[%s]tokens[%i]\n", s, tokens);
		mini->c[cmd].tokens = (char **)malloc(sizeof(char *) * tokens + 1);
		while (j < tokens)
		{
			skip_wspaces(s, &i);
			end = find_end(s, i);
			// printf("i = %i; end = %i\n", i, end);
			mini->c[cmd].tokens[j] = ft_substr(s, i, end - i);
			printf("[%s]\n", mini->c[cmd].tokens[j]);
			i = end;
			j++;
		}
		cmd++;
	}
	return (0);
}
