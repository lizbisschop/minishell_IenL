/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 10:49:36 by lbisscho       #+#    #+#                */
/*   Updated: 2019/11/12 14:07:13 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		len(long nb)
{
	int	i;

	i = 1;
	if (nb < 0)
	{
		nb = nb * -1;
		i++;
	}
	while (nb > 9)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

char			*ft_itoa(int n)
{
	char	*str;
	long	num;
	long	i;

	num = n;
	i = len(num);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (0);
	str[i] = '\0';
	i--;
	if (num < 0)
	{
		str[0] = '-';
		num = num * -1;
	}
	while (num > 9)
	{
		str[i] = 48 + (num % 10);
		num = num / 10;
		i--;
	}
	str[i] = 48 + num;
	return (str);
}
