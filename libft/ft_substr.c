/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/01 14:52:44 by lbisscho      #+#    #+#                 */
/*   Updated: 2020/11/15 14:59:19 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str2;

	i = start;
	j = 0;
	if (!s)
		return (0);
	if (ft_strlen(s) < i)
		return (ft_strdup(""));
	if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	str2 = malloc(sizeof(char) * len + 1);
	if (!str2)
		malloc_error();
	while (s[i] != '\0' && j < len)
	{
		str2[j] = s[i];
		i++;
		j++;
	}
	str2[j] = '\0';
	return (str2);
}
