/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   show_command_prompt.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: liz <liz@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 11:40:18 by liz           #+#    #+#                 */
/*   Updated: 2020/09/15 12:17:41 by liz           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void show_command_prompt(void)
{
	char buf[10000];
	getcwd(buf, 10000);
	ft_putstr_fd("\e[1;33m", 1);
	ft_putstr_fd(buf, 1);
	ft_putstr_fd("\e[0m", 1);
	write(1, "$ ", 2);
}