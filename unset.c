/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 18:19:12 by iboeters      #+#    #+#                 */
/*   Updated: 2020/11/09 18:19:13 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_token(int *i, t_mini *mini)
{
	while (mini->env[*i])
	{
		free(mini->env[*i]);
		mini->env[*i] = NULL;
		if (mini->env[*i + 1] != NULL)
			mini->env[*i] = ft_strdup(mini->env[*i + 1]);
		else
			break ;
		(*i)++;
	}
}

int		get_len_env(char *env)
{
	int i;

	i = 0;
	while (env[i] != '\0' && env[i] != '=')
	{
		i++;
	}
	return (i);
}

void	unset(char **tokens, t_mini *mini)
{
	int		i;
	int		tok;
	int		len;
	int		len_env;

	tok = 1;
	while (tokens[tok])
	{
		i = 0;
		len = ft_strlen(tokens[tok]);
		while (mini->env[i])
		{
			len_env = get_len_env(mini->env[i]);
			if (ft_strncmp(tokens[tok], mini->env[i], len) == 0
			&& len_env == len)
				unset_token(&i, mini);
			if (mini->env[i] == NULL)
				break ;
			i++;
		}
		tok++;
	}
	mini->exit_int = 0;
}
