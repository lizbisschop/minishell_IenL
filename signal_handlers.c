/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_handlers.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 14:46:10 by iboeters      #+#    #+#                 */
/*   Updated: 2020/11/16 10:22:17 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sig_child(int signal)
{
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

void	handle_sigint(int signal)
{
	write(2, "\b \b\b \b", 6);
	ft_putchar_fd('\n', 1);
	show_command_prompt();
	(void)signal;
}

void	handle_sigquit(int signal)
{
	write(2, "\b \b\b \b", 6);
	(void)signal;
}
