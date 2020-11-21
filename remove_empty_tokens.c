/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   remove_empty_tokens.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/21 11:34:46 by lbisscho      #+#    #+#                 */
/*   Updated: 2020/11/21 11:55:52 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    remove_empty_tokens_pipes(t_mini *mini, int i, int j)
{
	int old_i;
	int old_j;
	
	while (mini->pipes_c[mini->cmd].tokens[i])
	{
		if (ft_strlen(mini->pipes_c[mini->cmd].tokens[i]) == 0)
		{
			mini->pipes_c[mini->cmd].tok_amount--;
			if (mini->pipes_c[mini->cmd].tokens[i + 1] == NULL)
			{
				free(mini->pipes_c[mini->cmd].tokens[i]);
				mini->pipes_c[mini->cmd].tokens[i] = NULL;
				return ;
			}
			old_i = i;
			j = i + 1;
			while (mini->pipes_c[mini->cmd].tokens[j])
			{
				if (mini->pipes_c[mini->cmd].tokens[i])
					free(mini->pipes_c[mini->cmd].tokens[i]);
				mini->pipes_c[mini->cmd].tokens[i] = ft_strdup(mini->pipes_c[mini->cmd].tokens[j]);
				i++;
				j++;
			}
			mini->pipes_c[mini->cmd].tokens[i] = NULL;
			i = old_i;
		}
		i++;
	}
}

void    remove_empty_tokens(t_mini *mini, int i, int j)
{
	int old_i;
	int old_j;
	
	while (mini->c[mini->cmd].tokens[i])
	{
		if (ft_strlen(mini->c[mini->cmd].tokens[i]) == 0)
		{
			mini->c[mini->cmd].tok_amount--;
			if (mini->c[mini->cmd].tokens[i + 1] == NULL)
			{
				free(mini->c[mini->cmd].tokens[i]);
				mini->c[mini->cmd].tokens[i] = NULL;
				return ;
			}
			old_i = i;
			j = i + 1;
			while (mini->c[mini->cmd].tokens[j])
			{
				if (mini->c[mini->cmd].tokens[i])
					free(mini->c[mini->cmd].tokens[i]);
				mini->c[mini->cmd].tokens[i] = ft_strdup(mini->c[mini->cmd].tokens[j]);
				i++;
				j++;
			}
			mini->c[mini->cmd].tokens[i] = NULL;
			i = old_i;
		}
		i++;
	}
}