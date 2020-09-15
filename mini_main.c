/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_main.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: liz <liz@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 11:37:15 by liz           #+#    #+#                 */
/*   Updated: 2020/09/15 14:55:26 by liz           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void set_struct(t_mini *mini)
{
	mini->i = 0;
	mini->comma = 0;
}

int	check_syntax(char *input, t_mini *mini)
{
	int index;

	index = 0;
	while (input[index] != '\0')
	{
		if (input[index] == ';')
		{
			index++;
			while (input[index] != '\0' && ((input[index] >= 9 &&
			input[index] <= 12) || input[index] == 32))
				index++;
			if (input[index + 1] != '\0')
				mini->comma++;
			if (input[index] == ';')
				return (1);
		}
		index++;
	}
	return (0);
}

int main(void)
{
	t_mini mini;

	// get_input(&input);
	// printf("%s\n", input);
	while (1)
	{
	set_struct(&mini);
		show_command_prompt();
		mini.input = read_line();
		if (check_syntax(mini.input, &mini))
			ft_putstr_fd("Error:\nSyntax error near ';'.\n", 1);
		else if (ft_strlen(mini.input) > 0)
		{
			mini.sp_input = split_input(mini.input);
			which_command(&mini);
		}
		// show_command_prompt();
	}
	return (0);
}