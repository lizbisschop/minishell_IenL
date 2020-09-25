#include "minishell.h"

/*
** v CHANGE SO THAT QUOTES IN BETWEEN OTHER QUOTES DONT GET COUNTED
** A DIFFERENCE BETWEEN " AND ' QUOTES??
** escape character:
** -	split
** -	unquote
** v	multilines error
*/

char	*fill_string(int n_quotes, char c, char *s, int end)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = (char *)malloc((end - n_quotes + 1) * sizeof(char));
	while (i < end)
	{
		if (s[i] != c)
		{
			str[j] = s[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
	return (str);
}

char	*unquote(char *s)
{
	int		n_quotes;
	char	c;
	char	anti_c;
	int		i;
	int		end;

	n_quotes = 0;
	end = 0;
	i = 0;
	c = '\0';
	while (s[i] != '\0' && !(s[i] == '\'') && !(s[i] != '"'))
		i++;
	if (s[i] == '\'' || s[i] == '"')
	{
		c = s[i];
		if (c == '\'')
			anti_c = '"';
		else
			anti_c = '\'';
	}
	else
		return (s);
	while (s[end] != '\0')
	{
		if (s[end] == c)
			n_quotes++;
		if (s[end] == ' ' || (s[end] == anti_c && n_quotes % 2 == 0))
			break ;
		end++;
	}
	if (s)
	{
		free(s);
		s = NULL;
	}
	return (fill_string(n_quotes, c, s, end));
}
