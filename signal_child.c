/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_child.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/14 11:59:13 by iboeters      #+#    #+#                 */
/*   Updated: 2020/11/14 15:07:38 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sig_child(int signal)
{
	(void)signal;
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", 2);
	}
	else if (signal == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 2);
	}
}

void	signal_child(void)
{
	if (signal(SIGQUIT, &handle_sig_child) == SIG_ERR)
		ft_putstr_fd(strerror(errno), 2);
	if (signal(SIGINT, &handle_sig_child) == SIG_ERR)
		ft_putstr_fd(strerror(errno), 2);
}
