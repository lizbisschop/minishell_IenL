/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_main.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: liz <liz@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 11:37:15 by liz           #+#    #+#                 */
/*   Updated: 2020/09/14 17:13:35 by liz           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	char *input;

	// get_input(&input);
	// printf("%s\n", input);
	while (1)
	{
	show_command_prompt();
	input = read_line();
	which_command(input);
		// show_command_prompt();

	}
}