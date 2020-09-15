/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_input.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: liz <liz@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 12:14:09 by liz           #+#    #+#                 */
/*   Updated: 2020/09/14 18:07:20 by liz           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char 	*ft_realloc(char **str, int count)
{
	*str = (char *)malloc(sizeof(char) * count + 1);
	return (*str);
}

char	*read_line(void)
{
	char *line;

	line = NULL;
	get_next_line(0, &line);
	return (line);
}