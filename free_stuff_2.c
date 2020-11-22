/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_stuff_2.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/21 17:24:07 by lbisscho      #+#    #+#                 */
/*   Updated: 2020/11/22 12:28:29 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_mini *mini, char **array)
{
	int i;

	i = 0;
	while (mini->c[mini->cmd].tokens[i])
	{
		if (mini->c[mini->cmd].tokens[i])
			free(mini->c[mini->cmd].tokens[i]);
		i++;
	}
	i = 0;
	while (array[i])
	{
		if (array[i])
			free(array[i]);
		i++;
	}
	if (array)
		free(array);
	if (mini->c[mini->cmd].tokens)
		free(mini->c[mini->cmd].tokens);
}

void	free_tokens_pipes(t_mini *mini, char **array)
{
	int i;

	i = 0;
	while (mini->pipes_c[mini->cmd].tokens[i])
	{
		if (mini->pipes_c[mini->cmd].tokens[i])
			free(mini->pipes_c[mini->cmd].tokens[i]);
		i++;
	}
	i = 0;
	while (array[i])
	{
		if (array[i])
			free(array[i]);
		i++;
	}
	if (array)
		free(array);
	if (mini->pipes_c[mini->cmd].tokens)
		free(mini->pipes_c[mini->cmd].tokens);
}

void	close_and_free(t_mini *mini, char **s)
{
	close(mini->main_out);
	if (*s)
		free(*s);
}
