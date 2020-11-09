/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 18:18:36 by iboeters      #+#    #+#                 */
/*   Updated: 2020/11/09 18:18:37 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_pwd(void)
{
	char buf[4096];

	if (getcwd(buf, 4096) == NULL)
		return (0);
	return (ft_strdup(buf));
}

void	pwd(t_mini *mini)
{
	char buf[4096];

	if (getcwd(buf, 4096) == NULL)
	{
		err("pwd: ", "", 1, mini);
		mini->exit_int = 1;
		return ;
	}
	ft_putstr_fd(buf, 1);
	write(1, "\n", 1);
	mini->exit_int = 0;
}
