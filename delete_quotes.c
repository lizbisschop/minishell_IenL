/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   delete_quotes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: liz <liz@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/15 16:45:27 by liz           #+#    #+#                 */
/*   Updated: 2020/09/17 14:26:13 by liz           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		multi_lines(char *str, char c)
{
	int i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			count++;
		i++;
	}
	if (count % 2)
		return (1);
	return (0);
}


int		delete_quotes(t_mini *mini, char c)
{
	// int i;
	int j;

	// i = 0;
	j = 0;
	while(j < mini->cmds)
	{
		if (multi_lines(mini->sp_input[j], c))
		{
			ft_putstr_fd("Error:\nMultiline command.\n", 1);
			return (1);
		}
		// while (mini->sp_input[j][i] != '\0')
	}
	return (0);
}