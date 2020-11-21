/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_tokens.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/16 14:34:35 by lbisscho      #+#    #+#                 */
/*   Updated: 2020/11/21 15:38:25 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_mini *mini)
{
	int i;

	i = 0;
	while (mini->c[mini->cmd].tokens[i])
	{
		if (mini->c[mini->cmd].tokens[i])
			free(mini->c[mini->cmd].tokens[i]);
		i++;
	}
	if (mini->c[mini->cmd].tokens)
		free(mini->c[mini->cmd].tokens);
}

void	insert_array(int *j, char **array, char **new_tokens)
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

void	fill_tokens(char **array, char **new_tokens, t_mini *mini, char **str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (mini->c[mini->cmd].tokens[i])
	{
		if (i == mini->i_tok)
		{
			if (mini->use_string && ft_strlen(*str) != 0)
			{
				new_tokens[j] = ft_strdup(*str);
				j++;
			}
			insert_array(&j, array, new_tokens);
			i++;
		}
		else
		{
			new_tokens[j] = ft_strdup(mini->c[mini->cmd].tokens[i]);
			i++;
			j++;
		}
	}
	new_tokens[j] = NULL;
}

void	create_new_tokens(char **array, t_mini *mini, char *env, char **str)
{
	char	**new_tokens;

	mini->use_string = 0;
	if (env[0] == ' ' && ft_strlen(*str) != 0)
		mini->array_len++;
	mini->c[mini->cmd].tok_amount += mini->array_len - 1;
	new_tokens = (char **)malloc(sizeof(char *) *
	(mini->c[mini->cmd].tok_amount + 1));
	if (env[0] == ' ')
		mini->use_string = 1;
	fill_tokens(array, new_tokens, mini, str);
	if (array[mini->array_len - 1])
	{
		if (*str)
			free(*str);
		(*str) = ft_strdup(array[mini->array_len - 1]);
	}
	// free_tokens(mini);
	mini->c[mini->cmd].tokens = new_tokens;
	mini->i_tok += mini->array_len - 1;
}

void	expand_tokens(t_mini *mini, char **str, int i, char *env)
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
	mini->array_len = array_len;
	create_new_tokens(array, mini, env, str);
}
