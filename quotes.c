#include "minishell.h"

/*
** v CHANGE SO THAT QUOTES IN BETWEEN OTHER QUOTES DONT GET COUNTED
** A DIFFERENCE BETWEEN " AND ' QUOTES??
** escape character:
** -	split
** -	unquote
** v	multilines error
*/

char	*fill_string(int n_quotes, char *s)
{
	// int		i;
	// int		j;
	// char	*str;

	// i = 0;
	// j = 0;
	// str = (char *)malloc((end - n_quotes + 1) * sizeof(char));
	// while (i < end)
	// {
	// 	if (s[i] != c)
	// 	{
	// 		str[j] = s[i];
	// 		j++;
	// 	}
	// 	i++;
	// }
	// str[j] = '\0';
	// return (str);
	(void)n_quotes;
	return (s);
}

char	*unquote(char *s)
{
	int		n_quotes;
	char	c;
	char	anti_c;
	char	temp;
	int		i;

	n_quotes = 0;
	i = 0;
	c = '\'';
	anti_c = '"';
	while (s[i] != '\0')
	{
		// printf("[%s]\t\t[%c][%c][%i]\n", &s[i], c, anti_c, n_quotes);
		if (s[i] == c)
			n_quotes++;
		else if (s[i] == anti_c && n_quotes % 2 == 0)
		{
			n_quotes++;
			temp = c;
			c = anti_c;
			anti_c = temp;
			// printf("%c%c%c\n", c, anti_c, temp);
		}
		i++;
	}
	if (n_quotes == 0)
		return (s);
	if (s)
	{
		free(s);
		s = NULL;
	}
	return (fill_string(n_quotes, s));
	return (0);
}
