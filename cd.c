/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: liz <liz@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/17 11:30:01 by liz           #+#    #+#                 */
/*   Updated: 2020/09/21 14:45:33 by liz           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(char *str, t_mini *mini, char **envp)
{
	char *home;
	int place;

	place = 0;
	while (envp[place])
	{
		if (ft_strncmp("HOME=", envp[place], 5) == 0)
		{
			home = ft_strdup(&envp[place][5]);
		}
		place++;
	}
	printf("%s\n", home);
	skip_whitespaces(str, mini);
	if (str[mini->i] == '~')
	{
		chdir(home);
		mini->i++;
	}
	else if (str[mini->i] == '/')
		chdir("//");
	else if (ft_strncmp("/root", &str[mini->i], 5) == 0)
		chdir("/root");
	else
		chdir(&str[mini->i]);
}
