/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   which_command.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: liz <liz@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 14:20:20 by liz           #+#    #+#                 */
/*   Updated: 2020/09/14 15:41:30 by liz           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int find_command(char *input, int *i)
{
	if (ft_strncmp("echo ", &input[*i], 5))
	{
		*i += 4;
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
		// cmd = 0;
		skipping_spaces(input, &i);
		cmd = find_command(input, &i);
		if (cmd == 1)
			break ;
		i++;
	}
	echo(&input[i]);
}