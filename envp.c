/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   envp.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: liz <liz@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/21 12:51:09 by liz           #+#    #+#                 */
/*   Updated: 2020/09/22 11:37:37 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_command(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		ft_putstr_fd(envp[i], 1);
		write(1, "\n", 1);
		i++;
	}
}