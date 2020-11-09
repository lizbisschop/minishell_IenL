/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_stuff.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 18:18:01 by iboeters      #+#    #+#                 */
/*   Updated: 2020/11/09 18:18:02 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_mini_c(t_mini *mini)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (j < mini->cmds)
	{
		i = 0;
		if (mini->c != 0)
		{
			while (mini->c[j].tokens[i])
			{
				if (mini->c[j].tokens[i])
					free(mini->c[j].tokens[i]);
				i++;
			}
			if (mini->c[j].tokens)
				free(mini->c[j].tokens);
			j++;
		}
		else
			break ;
	}
	if (mini->c)
		free(mini->c);
}

void	free_sp_input(t_mini *mini)
{
	int j;

	j = 0;
	if (mini->sp_input[j])
	{
		while (mini->sp_input[j])
		{
			if (mini->sp_input[j])
				free(mini->sp_input[j]);
			j++;
		}
	}
}

void	free_pipes_c(t_mini *mini)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (j < mini->pipe_cmds && mini->pipes_c[j].tokens)
	{
		i = 0;
		if (mini->pipes_c != 0)
		{
			while (mini->pipes_c[j].tokens[i])
			{
				if (mini->pipes_c[j].tokens[i])
					free(mini->pipes_c[j].tokens[i]);
				i++;
			}
			if (mini->pipes_c[j].tokens)
				free(mini->pipes_c[j].tokens);
			j++;
		}
		else
			break ;
	}
	if (mini->pipes_c)
		free(mini->pipes_c);
}

void	free_stuff(t_mini *mini)
{
	free_mini_c(mini);
	free_sp_input(mini);
	if (mini->sp_input)
		free(mini->sp_input);
}
