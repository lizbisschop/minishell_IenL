/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 13:24:07 by lbisscho       #+#    #+#                */
/*   Updated: 2019/11/14 16:56:28 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*string;

	i = 0;
	string = (unsigned char*)b;
	while (i < len)
	{
		string[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
