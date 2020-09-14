/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstsize_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/15 14:51:20 by lbisscho       #+#    #+#                */
/*   Updated: 2019/11/20 13:41:45 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int i;

	i = 0;
	if (lst)
	{
		while (lst->next != NULL)
		{
			i++;
			lst = lst->next;
		}
		if (lst->next == NULL)
			i++;
	}
	return (i);
}
