/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: liz <liz@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/17 11:30:01 by liz           #+#    #+#                 */
/*   Updated: 2020/09/17 14:08:40 by liz           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void 	cd(char *str, t_mini *mini)
{
	printf("%s\n", &str[mini->i]);
	skip_whitespaces(str, mini);
	if (str[mini->i] == '~')
	{
		printf("hello\n");
		printf("%d\n", chdir("/home"));
		
		mini->i++;
	}
	if (str[mini->i] == '//')
		chdir("//");
	if (str[mini->i] == )
	chdir(&str[mini->i]);
}
