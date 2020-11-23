/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 18:18:20 by iboeters      #+#    #+#                 */
/*   Updated: 2020/11/23 13:04:41 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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

void	skip_quoted(char *s, int *i)
{
	if (s[*i] == '\\' && s[*i + 1] != '\0')
		(*i) += 2;
	else if (s[*i] == '\\' && s[*i + 1] == '\0')
		(*i)++;
	else if (s[*i] == '"')
	{
		(*i)++;
		while (s[*i] != '\0' && s[*i] != '"')
		{
			if (s[*i] == '\\' && s[*i + 1] != '\0')
				(*i)++;
			(*i)++;
		}
		if (s[*i] == '"')
			(*i)++;
	}
	else if (s[*i] == '\'')
	{
		(*i)++;
		while (s[*i] != '\0' && s[*i] != '\'')
			(*i)++;
		if (s[*i] == '\'')
			(*i)++;
	}
}

char	*ft_strdup_free(char **s1)
{
	size_t	i;
	char	*s2;

	s2 = (char *)malloc(sizeof(char) * (ft_strlen(*s1) + 1));
	if (!s2)
		malloc_error();
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
