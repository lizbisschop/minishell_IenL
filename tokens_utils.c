/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 18:19:06 by iboeters      #+#    #+#                 */
/*   Updated: 2020/11/09 18:19:07 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ret_del(char *s, int i)
{
	if (s[i] == '>' && s[i + 1] == '>')
		i = i + 2;
	else
		i++;
	return (i);
}
