/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 16:46:00 by lbisscho      #+#    #+#                 */
/*   Updated: 2020/11/07 14:01:42 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*destination;
	unsigned char	*source;

	i = 0;
	destination = (unsigned char*)dst;
	source = (unsigned char*)src;
	if (!destination && !source)
		return (0);
	while (i < n)
	{
		destination[i] = source[i];
		i++;
	}
	return (dst);
}
