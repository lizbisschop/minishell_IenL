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

void	skip_whitespaces(char *str, t_mini *mini)
{
	while (str[mini->i] != '\0' && ((str[mini->i] >= 9 && str[mini->i] <= 12)
	|| str[mini->i] == 32))
	{
		mini->i++;
	}
}

char	*ft_strdup_free(char **s1)
{
	size_t	i;
	char	*s2;

	s2 = (char *)malloc(sizeof(char) * (ft_strlen(*s1) + 1));
	if (!s2)
		return (0);
	i = 0;
	while ((*s1)[i] != '\0')
	{
		s2[i] = (*s1)[i];
		i++;
	}
	s2[i] = '\0';
	if (*s1)
		free(*s1);
	return (s2);
}
