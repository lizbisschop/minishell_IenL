/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_tokens.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/16 14:34:35 by lbisscho      #+#    #+#                 */
/*   Updated: 2020/11/20 17:57:03 by iboeters      ########   odam.nl         */
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

void	fill_tokens_with_str(char **array, char **new_tokens, t_mini *mini, char **str)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	while (mini->c[mini->cmd].tokens[i])
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
			new_tokens[j] = ft_strdup(mini->c[mini->cmd].tokens[i]);
			i++;
			j++;
		}
	}
	new_tokens[j] = NULL;
}

void	fill_tokens(char **array, char **new_tokens, t_mini *mini)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	while (mini->c[mini->cmd].tokens[i])
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
			new_tokens[j] = ft_strdup(mini->c[mini->cmd].tokens[i]);
			i++;
			j++;
		}
	}
	new_tokens[j] = NULL;
}

void	add_tokens(char **array, int array_len, t_mini *mini, char *env, char **str)
{
	char	**new_tokens;

	if (env[0] == ' ' && ft_strlen(*str) != 0)
		array_len++;
	mini->array_len = array_len;
	mini->c[mini->cmd].tok_amount += array_len;
	new_tokens = (char **)malloc(sizeof(char *) *
	(mini->c[mini->cmd].tok_amount + 1));
	if (env[0] == ' ')
		fill_tokens_with_str(array, new_tokens, mini, str);
	else
		fill_tokens(array, new_tokens, mini);
	if (array[array_len - 1])
	{
		if (*str)
			free(*str);
		(*str) = ft_strdup(array[array_len - 1]);
	}
	mini->c[mini->cmd].tokens = new_tokens;
	mini->i_tok += array_len - 1;
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
	add_tokens(array, array_len, mini, env, str);
}
