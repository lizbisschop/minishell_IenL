/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/14 12:01:27 by lbisscho       #+#    #+#                */
/*   Updated: 2019/12/05 14:34:52 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_string_count(char const *s, char c)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (s[i] == 0)
		return (0);
	if (c == 0)
		return (1);
	while (s[i] == c && s[i] != '\0')
		i++;
	if (s[i] == 0)
		return (0);
	while (s[i] != '\0')
	{
		i++;
		if (s[i] == c)
		{
			while (s[i] == c && s[i] != '\0')
				i++;
			if (s[i] != '\0')
				j++;
		}
	}
	return (j + 1);
}

static int		ft_string_len(char const *str, char c, int k)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i] == c)
		i++;
	while (str[i] != '\0' && k > 0)
	{
		i++;
		if (str[i] == c)
			k--;
		while (str[i] == c)
			i++;
	}
	while (str[i] != c && str[i] != '\0')
	{
		i++;
		j++;
	}
	return (j + 1);
}

static char		*ft_make_string(char *string, char const *str, char c, int k)
{
	int i;

	i = 0;
	while (str[i] == c)
		i++;
	while (str[i] != '\0' && k > 0)
	{
		i++;
		if (str[i] == c)
			k--;
		while (str[i] == c)
			i++;
	}
	while (str[i] != c && str[i] != '\0')
	{
		string[k] = str[i];
		i++;
		k++;
	}
	string[k] = '\0';
	return (string);
}

static void		ft_free_split(char **str_ar, int k)
{
	while (k >= 0)
	{
		free(str_ar[k]);
		k--;
	}
	free(str_ar);
}

char			**ft_split(char const *s, char c)
{
	char	**str_ar;
	int		k;
	int		str_count;

	if (!s)
		return (0);
	k = 0;
	str_count = ft_string_count(s, c);
	str_ar = (char**)malloc(sizeof(char*) * (str_count + 1));
	if (!str_ar)
		return (0);
	while (k < str_count)
	{
		str_ar[k] = (char*)malloc(sizeof(char) * ft_string_len(s, c, k));
		if (!str_ar[k])
		{
			ft_free_split(str_ar, k);
			return (0);
		}
		str_ar[k] = ft_make_string(str_ar[k], s, c, k);
		k++;
	}
	str_ar[k] = 0;
	return (str_ar);
}
