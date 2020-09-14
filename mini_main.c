/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_main.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: liz <liz@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 11:37:15 by liz           #+#    #+#                 */
/*   Updated: 2020/09/14 15:24:09 by liz           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	char *input;

	show_command_prompt();
	// get_input(&input);
	input = read_line();
	// printf("%s\n", input);
	which_command(input);
	show_command_prompt();
	while (1)
	{
		// show_command_prompt();

	}
}