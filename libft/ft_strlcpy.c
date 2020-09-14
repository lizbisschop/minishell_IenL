/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 15:25:51 by lbisscho       #+#    #+#                */
/*   Updated: 2019/11/14 17:19:19 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	char	*destination;
	char	*source;

	i = 0;
	j = 0;
	if (!dst && !src)
		return (0);
	destination = (char*)dst;
	source = (char*)src;
	while (source[i] != '\0')
		i++;
	if (dstsize == 0)
		return (i);
	while (source[j] != '\0' && j + 1 < dstsize)
	{
		destination[j] = source[j];
		j++;
	}
	destination[j] = '\0';
	return (i);
}
