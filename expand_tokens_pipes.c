/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_tokens_pipes.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/16 19:36:29 by lbisscho      #+#    #+#                 */
/*   Updated: 2020/11/21 17:24:20 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	insert_array_pipes(int *j, char **array, char **new_tokens)
{
	int k;

	k = 0;
	while (array[k])
	{
		new_tokens[*j] = ft_strdup(array[k]);
		k++;
		(*j)++;
	}
}

void	fill_tokens_pipes(char **array, char **new_tokens,
t_mini *mini, char **str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (mini->pipes_c[mini->cmd].tokens[i])
	{
		if (i == mini->i_tok)
		{
			if (mini->use_string && ft_strlen(*str) != 0)
			{
				new_tokens[j] = ft_strdup(*str);
				j++;
			}
			insert_array_pipes(&j, array, new_tokens);
			i++;
		}
		else
		{
			new_tokens[j] = ft_strdup(mini->pipes_c[mini->cmd].tokens[i]);
			i++;
			j++;
		}
	}
	new_tokens[j] = NULL;
}

void	create_new_tokens_pipes(char **array,
t_mini *mini, char *env, char **str)
{
	char	**new_tokens;

	mini->use_string = 0;
	if (env[0] == ' ' && ft_strlen(*str) != 0)
		mini->array_len++;
	mini->pipes_c[mini->cmd].tok_amount += mini->array_len - 1;
	new_tokens = (char **)malloc(sizeof(char *) *
	(mini->pipes_c[mini->cmd].tok_amount + 1));
	if (env[0] == ' ')
		mini->use_string = 1;
	fill_tokens_pipes(array, new_tokens, mini, str);
	if (array[mini->array_len - 1])
	{
		if (*str)
			free(*str);
		(*str) = ft_strdup(array[mini->array_len - 1]);
	}
	free_tokens_pipes(mini, array);
	mini->pipes_c[mini->cmd].tokens = new_tokens;
	mini->i_tok += mini->array_len - 1;
}

void	check_space_env_pipes(char **old_str, char **str, int i)
{
	*old_str = ft_substr(*str, 0, i);
	if (*str)
		free(*str);
	(*str) = ft_strdup(*old_str);
	if (*old_str)
		free(*old_str);
}

void	expand_tokens_pipes(t_mini *mini, char **str, int i, char *env)
{
	char	**array;
	int		array_len;
	char	*old_str;

	array_len = 0;
	if (ft_strlen(env) == 0)
		return ;
	(*str) = gnl_strjoin(*str, env);
	array = ft_split(&(*str)[i], ' ');
	if (env[0] == ' ')
		check_space_env_pipes(&old_str, str, i);
	else
	{
		old_str = ft_substr(*str, 0, i);
		array[0] = ft_strjoin_read(old_str, array[0]);
		if (old_str)
			free(old_str);
	}
	while (array[array_len])
		array_len++;
	mini->array_len = array_len;
	create_new_tokens_pipes(array, mini, env, str);
}
