/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 18:55:17 by lbisscho      #+#    #+#                 */
/*   Updated: 2020/11/07 14:01:45 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*destination;
	unsigned char	*source;

	i = 0;
	destination = (unsigned char*)dst;
	source = (unsigned char*)src;
	if (!dst && !source)
		return (0);
	if (source < destination)
	{
		while (len > 0)
		{
			len--;
			destination[len] = source[len];
		}
	}
	else
		while (i < len)
		{
			destination[i] = source[i];
			i++;
		}
	return (destination);
}
