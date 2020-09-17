/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   show_command_prompt.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: liz <liz@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/17 14:23:11 by liz           #+#    #+#                 */
/*   Updated: 2020/09/17 14:36:49 by liz           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	show_command_prompt(void)
{
	char buf[10000];
	getcwd(buf, 10000);
	ft_putstr_fd("\e[1;33m~", 1);
	ft_putstr_fd(buf, 1);
	ft_putstr_fd("\e[0m", 1);
	write(1, "$ ", 2);
}
