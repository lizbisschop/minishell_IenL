#include "minishell.h"

/*
** CHANGE SO THAT QUOTES IN BETWEEN OTHER QUOTES DONT GET COUNTED
** A DIFFERENCE BETWEEN " AND ' QUOTES??
** escape character:
** -	split
** -	unquote
** v	multilines error
*/

char	*fill_string(int n_quotes, char c, char *line, t_mini *mini)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = (char *)malloc((mini->end_string - n_quotes + 1) * sizeof(char));
	while (i < mini->end_string)
	{
		if (line[i] != c)
		{
			str[j] = line[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
	return (str);
}

char	*unquote(char *line, t_mini *mini, int command)
{
	int		n_quotes;
	char	c;
	char	anti_c;
	int		i;

	n_quotes = 0;
	mini->end_string = 0;
	i = 0;
	c = '\0';
	while (line[i] != '\0' && !(line[i] == '\'') && !(line[i] != '"'))
		i++;
	if (line[i] == '\'' || line[i] == '"')
	{
		c = line[i];
		if (c == '\'')
			anti_c = '"';
		else
			anti_c = '\'';
	}
	while (line[mini->end_string] != '\0')
	{
		if (line[mini->end_string] == c)
		{
			mini->i++;
			n_quotes++;
		}
		if ((line[mini->end_string] == ' ' || (line[mini->end_string] == anti_c
		&& command == 0)) && n_quotes % 2 == 0)
			break ;
		mini->end_string++;
	}
	return (fill_string(n_quotes, c, line, mini));
}
