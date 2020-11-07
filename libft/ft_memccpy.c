/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memccpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 17:34:09 by lbisscho      #+#    #+#                 */
/*   Updated: 2020/11/07 14:01:32 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*destination;
	unsigned char	*source;
	unsigned char	cha;

	i = 0;
	destination = (unsigned char*)dst;
	source = (unsigned char*)src;
	cha = (unsigned char)c;
	if (!dst && !src)
		return (0);
	while (i < n)
	{
		destination[i] = source[i];
		if (source[i] == cha)
		{
			return ((void *)(dst + i + 1));
		}
		i++;
	}
	return (0);
}
