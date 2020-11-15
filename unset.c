/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 18:19:12 by iboeters      #+#    #+#                 */
/*   Updated: 2020/11/15 14:14:11 by lbisscho      ########   odam.nl         */
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

void	is_not_alpha(char **tokens, int tok, t_mini *mini)
{
	if (!ft_isalpha(tokens[tok][0]))
	{
		ft_putstr_fd("bash: unset: `", 2);
		ft_putstr_fd(tokens[tok], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		mini->exit_int = 1;
	}
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
		is_not_alpha(tokens, tok, mini);
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
}
