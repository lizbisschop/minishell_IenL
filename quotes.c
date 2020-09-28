#include "minishell.h"

/*
** v CHANGE SO THAT QUOTES IN BETWEEN OTHER QUOTES DONT GET COUNTED
** A DIFFERENCE BETWEEN " AND ' QUOTES??
** escape character (\):
** v	split
** v	unquote
** v	multilines error
*/

char	*fill_string(int len, int n_quotes, char **s)
{
	char	q;
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	q = '\0';
	str = (char *)malloc(sizeof(char) * (len - n_quotes + 1));
	if (!str)
	{
		ft_putstr_fd("Malloc failed\n", 1);
		exit (1);
	}
	while ((*s)[i] != '\0')
	{
		if ((*s)[i] == '\'' || (*s)[i] == '"')
		{
			q = (*s)[i];
			i++;
			while ((*s)[i] != q && (*s)[i] != '\0')
			{
				if (q == '"' && (*s)[i] == '\\' &&
				((*s)[i + 1] == q || (*s)[i + 1] == '\\' || (*s)[i + 1] == '$'))
					i++;
				str[j] = (*s)[i];
				j++;
				if ((*s)[i] != '\0')
					i++;
			}
		}
		else if ((*s)[i] != '\\')
		{
			str[j] = (*s)[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
	if (*s)
	{
		free(*s);
		*s = NULL;
	}
	return (str);
}

char	*unquote(char **s)
{
	int		n_quotes;
	char	q;
	char	anti_q;
	char	temp;
	int		i;

	n_quotes = 0;
	i = 0;
	q = '\'';
	anti_q = '"';
	while ((*s)[i] != '\0')
	{
		// printf("[%s]\t\t[%c][%c][%i]\n", &s[i], q, anti_q, n_quotes);
		if ((*s)[i] == q)
			n_quotes++;
		else if ((*s)[i] == '\\' && (*s)[i + 1] != '\0')
			i++;
		else if ((*s)[i] == anti_q && n_quotes % 2 == 0)
		{
			n_quotes++;
			temp = q;
			q = anti_q;
			anti_q = temp;
			// printf("%c%c%c\n", q, anti_q, temp);
		}
		i++;
	}
	if (n_quotes == 0)
		return (*s);
	return (fill_string(i, n_quotes, s));
}
