/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_tokens_pipes.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/16 19:36:29 by lbisscho      #+#    #+#                 */
/*   Updated: 2020/11/19 16:57:20 by liz           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens_pipes(t_mini *mini)
{
	int i;

	i = 0;
	while (mini->pipes_c[mini->cmd].tokens[i])
	{
		if (mini->pipes_c[mini->cmd].tokens[i])
			free(mini->pipes_c[mini->cmd].tokens[i]);
		i++;
	}
	if (mini->pipes_c[mini->cmd].tokens)
		free(mini->pipes_c[mini->cmd].tokens);
}

void	add_tokens_pipes(char **array, int array_len, t_mini *mini, char *env, char **str)
{
	char	**new_tokens;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	if (env[0] == ' ' && ft_strlen(*str) != 0)
		array_len++;
	mini->array_len = array_len;
	mini->pipes_c[mini->cmd].tok_amount += array_len;
	new_tokens = (char **)malloc(sizeof(char *) *
	(mini->pipes_c[mini->cmd].tok_amount + 1));
	if (env[0] == ' ')
	{
		while (mini->pipes_c[mini->cmd].tokens[i])
		{
			if (i == mini->i_tok)
			{
				if (ft_strlen(*str) != 0)
				{
					new_tokens[j] = ft_strdup(*str);
					j++;
				}
				while (array[k])
				{
					new_tokens[j] = ft_strdup(array[k]);
					k++;
					j++;
				}
				i++;
			}
			else
			{
				new_tokens[j] = ft_strdup(mini->pipes_c[mini->cmd].tokens[i]);
				i++;
				j++;
			}
		}
	}
	else
	{
		while (mini->pipes_c[mini->cmd].tokens[i])
		{
			if (i == mini->i_tok)
			{
				while (array[k])
				{
					new_tokens[j] = ft_strdup(array[k]);
					k++;
					j++;
				}
				i++;
			}
			else
			{
				new_tokens[j] = ft_strdup(mini->pipes_c[mini->cmd].tokens[i]);
				i++;
				j++;
			}
		}
	}
	if (array[array_len - 1])
	{
		if (*str)
			free(*str);
		(*str) = ft_strdup(array[array_len - 1]);
	}
	new_tokens[j] = NULL;
	mini->pipes_c[mini->cmd].tokens = new_tokens;
	mini->i_tok += array_len - 1;
}

void	expand_tokens_pipes(t_mini *mini, char **str, int i, char *env)
{
	char	**array;
	int		array_len;

	array_len = 0;
	if (ft_strlen(env) == 0)
		return ;
	(*str) = gnl_strjoin(*str, env);
	array = ft_split(&(*str)[i], ' ');
	if (env[0] == ' ')
		(*str) = ft_substr(*str, 0, i);
	else
		array[0] = ft_strjoin_read(ft_substr(*str, 0, i), array[0]);
	while (array[array_len])
		array_len++;
	add_tokens_pipes(array, array_len, mini, env, str);
}
