/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   remove_empty_tokens.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/21 11:34:46 by lbisscho      #+#    #+#                 */
/*   Updated: 2020/11/21 12:18:16 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_token_pipes(t_mini *mini, int *old_i, int *i, int *j)
{
	mini->pipes_c[mini->cmd].tok_amount--;
	if (mini->pipes_c[mini->cmd].tokens[*i + 1] == NULL)
	{
		free(mini->pipes_c[mini->cmd].tokens[*i]);
		mini->pipes_c[mini->cmd].tokens[*i] = NULL;
		return ;
	}
	*old_i = *i;
	*j = *i + 1;
	while (mini->pipes_c[mini->cmd].tokens[*j])
	{
		if (mini->pipes_c[mini->cmd].tokens[*i])
			free(mini->pipes_c[mini->cmd].tokens[*i]);
		mini->pipes_c[mini->cmd].tokens[*i] =
		ft_strdup(mini->pipes_c[mini->cmd].tokens[*j]);
		(*i)++;
		(*j)++;
	}
	mini->pipes_c[mini->cmd].tokens[*i] = NULL;
	*i = *old_i;
}

void	remove_empty_tokens_pipes(t_mini *mini)
{
	int i;
	int j;
	int old_i;

	i = 0;
	j = 0;
	while (mini->pipes_c[mini->cmd].tokens[i])
	{
		if (ft_strlen(mini->pipes_c[mini->cmd].tokens[i]) == 0)
			remove_token_pipes(mini, &old_i, &i, &j);
		else
			i++;
	}
}

void	remove_token(t_mini *mini, int *old_i, int *i, int *j)
{
	mini->c[mini->cmd].tok_amount--;
	if (mini->c[mini->cmd].tokens[*i + 1] == NULL)
	{
		free(mini->c[mini->cmd].tokens[*i]);
		mini->c[mini->cmd].tokens[*i] = NULL;
		return ;
	}
	*old_i = *i;
	*j = *i + 1;
	while (mini->c[mini->cmd].tokens[*j])
	{
		if (mini->c[mini->cmd].tokens[*i])
			free(mini->c[mini->cmd].tokens[*i]);
		mini->c[mini->cmd].tokens[*i] =
		ft_strdup(mini->c[mini->cmd].tokens[*j]);
		(*i)++;
		(*j)++;
	}
	mini->c[mini->cmd].tokens[*i] = NULL;
	*i = *old_i;
}

void	remove_empty_tokens(t_mini *mini)
{
	int i;
	int j;
	int old_i;

	i = 0;
	j = 0;
	while (mini->c[mini->cmd].tokens[i])
	{
		if (ft_strlen(mini->c[mini->cmd].tokens[i]) == 0)
			remove_token(mini, &old_i, &i, &j);
		else
			i++;
	}
}
