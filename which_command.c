/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   which_command.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: liz <liz@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 14:20:20 by liz           #+#    #+#                 */
/*   Updated: 2020/09/14 18:10:05 by liz           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int find_command(char *input, int *i)
{
	// printf("find command\n");
	if (ft_strncmp("echo ", &input[*i], 5) == 0)
	{
		*i += 5;
		// printf(" echo found\n");
		return (1);
	}
	return (0);
}

void skipping_spaces(char *str, int *count)
{
	while (str[*count] != '\0' && str[*count] == ' ')
	{
		(*count)++;	
	}
}

void 	which_command(char *input)
{
	int i;
	int cmd;

	i = 0;
	while (input[i] != '\0')
	{
		cmd = 0;
		skipping_spaces(input, &i);
		cmd = find_command(input, &i);
		if (cmd == 1)
			i = echo(&input[i]);
		// else if (cmd == 0)
		// 	ft_putstr_fd("Error:\nCommand not found.\n", 1);
		i++;
	}
}
