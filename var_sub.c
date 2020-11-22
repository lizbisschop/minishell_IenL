/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   var_sub.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/22 12:21:00 by lbisscho      #+#    #+#                 */
/*   Updated: 2020/11/22 16:00:13 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**fill_old_tokens(char **tokens)
{
	char	**old_tokens;
	int		i;

	i = 0;
	while (tokens[i])
		i++;
	old_tokens = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (tokens[i])
	{
		old_tokens[i] = ft_strdup(tokens[i]);
		i++;
	}
	old_tokens[i] = NULL;
	return (old_tokens);
}

void	var_sub(char **tokens, t_mini *mini, int cmd)
{
	int		i;
	char	**old_tokens;
	char	*old_token;

	i = 0;
	old_tokens = fill_old_tokens(tokens);
	i = 0;
	mini->cmd = cmd;
	while (old_tokens[i])
	{
		old_token = ft_strdup(old_tokens[i]);
		mini->array_len = 0;
		mini->i_tok = i;
		check_for_dollar(&old_token, mini);
		if (old_token)
			free(old_token);
		if (mini->piped == 1)
			remove_empty_token_pipes(mini, mini->i_tok);
		else
			remove_empty_token(mini, mini->i_tok);
		i++;
	}
	free_old_tokens(&old_tokens);
}
