#include "minishell.h"

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
			if (s[i] == '\'')
			{
				// printf("'\n");
				i++;
				while (s[i] != '\0' && s[i] != '\'')
					i++;
				if (s[i] == '\'')
					i++;
			}
			else if (s[i] == '"')
			{
				// printf("\"\n");
				i++;
				while (s[i] != '\0' && s[i] != '"')
					i++;
				if (s[i] == '"')
					i++;
			}
			else if (is_delimiter(s[i]))
			{
				// printf("break1%s\n", &s[i]);
				if (s[i] == '>' && s[i + 1] == '>')
					i = i + 2;
				else
					i++;
				break ;
			}
			else if (ft_isascii(s[i]))
			{
				while (s[i] != '\0' && s[i] != '\'' && s[i]!= '"' &&
				!is_delimiter(s[i]) && !is_whitespace(s[i]) && ft_isascii(s[i]))
					i++;
				if (s[i] != '\'' && s[i]!= '"')
					break ;
				// printf("break2%s\n", &s[i]);
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
		if (s[i] == '\'')
		{
			// printf("singlequotes\n");
			i++;
			while (s[i] != '\0' && s[i] != '\'')
				i++;
			if (s[i] == '\'')
				i++;
		}
		else if (s[i] == '"')
		{
			// printf("doublequotes\n");
			i++;
			while (s[i] != '\0' && s[i] != '"')
				i++;
			if (s[i] == '"')
				i++;
		}
		else if (is_delimiter(s[i]))
		{
			// printf("end_found1%s\n", &s[i]);
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
			// printf("end_found2%s\n", &s[i]);
			if (s[i] != '\'' && s[i]!= '"')
				return (i);
		}
		else
			i++;
	}
	return (i);
}

int		tokens(t_mini *mini)
{
	int		end;
	int		i;
	int		j;
	int		tokens;
	int		cmd;
	char	*s;

	cmd = 0;
	mini->c = (t_command *)malloc(sizeof(t_command) * (mini->cmds + 1));
	if (mini->c == (void*)-1)
	{
		ft_putstr_fd("Malloc fail\n", 1);
		exit(0);
	}
	while (cmd < mini->cmds)
	{
		i = 0;
		j = 0;
		s = mini->sp_input[cmd];
		tokens = token_amount(s);
		mini->c[cmd].tok_amount = tokens;
		// printf("whole string[%s]\ntokens[%i]:\n", s, tokens);
		mini->c[cmd].tokens = (char **)malloc(sizeof(char *) * tokens + 1);
		if (!(mini->c[cmd].tokens))
		{
			ft_putstr_fd("Malloc fail\n", 1);
			exit(0);
		}
		while (j < tokens)
		{
			skip_wspaces(s, &i);
			end = tok_end(s, i);
			// printf("i = %i; end = %i\n", i, end);
			mini->c[cmd].tokens[j] = ft_substr(s, i, end - i);
			printf("[%s]\n", mini->c[cmd].tokens[j]);
			i = end;
			j++;
		}
		mini->c[cmd].tokens[j] = '\0';
		cmd++;
	}
	// mini->c[cmd] = NULL;
	// if (s)
	// 	free(s);
	// printf("\n*\n*\n*\n");
	return (0);
}
