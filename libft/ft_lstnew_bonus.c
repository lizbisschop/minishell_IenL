/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnew_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/15 13:08:28 by lbisscho       #+#    #+#                */
/*   Updated: 2019/11/20 13:40:17 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list *element;

	element = malloc(sizeof(t_list));
	if (element == 0)
		return (0);
	element->content = content;
	element->next = NULL;
	return (element);
}
