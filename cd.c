/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: liz <liz@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/17 11:30:01 by liz           #+#    #+#                 */
/*   Updated: 2020/09/21 12:26:52 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void 	cd(char *str, t_mini *mini)
{
	skip_whitespaces(str, mini);
	if (str[mini->i] == '~')
	{
		chdir("/home");
		mini->i++;
	}
	else if (str[mini->i] == '/')
		chdir("//");
	if (ft_strncmp("/root", &str[mini->i], 5))
		chdir("/root");
	chdir(&str[mini->i]);
}
