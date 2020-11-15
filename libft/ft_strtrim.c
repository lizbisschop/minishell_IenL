/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/02 10:27:49 by lbisscho      #+#    #+#                 */
/*   Updated: 2020/11/15 14:59:10 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	begin(char const *s1, char const *s2)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (s2[j] != '\0' && s1[i] != '\0')
	{
		if (s1[i] == s2[j] && s2[j] != '\0')
		{
			i++;
			j = 0;
		}
		else if (s1[i] != s2[j] && s2[j] != '\0')
			j++;
	}
	return (i);
}

static int	end(char const *s1, char const *s2)
{
	int i;
	int j;

	i = ft_strlen(s1) - 1;
	j = 0;
	while (s2[j] != '\0' && i >= 0)
	{
		if (s1[i] == s2[j])
		{
			i--;
			j = 0;
		}
		else if (s1[i] != s2[j] && s2[j] != '\0')
			j++;
	}
	return (i);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		k;
	char	*str3;

	if (!s1 || !set)
		return (0);
	i = begin(s1, set);
	j = end(s1, set);
	k = 0;
	if (!s1)
		return (0);
	if (i >= j)
		return (ft_strdup(""));
	str3 = malloc(sizeof(char) * (j - i + 2));
	if (!str3)
		malloc_error();
	while (i <= j)
	{
		str3[k] = s1[i];
		k++;
		i++;
	}
	str3[k] = '\0';
	return (str3);
}
