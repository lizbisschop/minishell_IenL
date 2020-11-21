/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_env_var.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 14:35:03 by lbisscho      #+#    #+#                 */
/*   Updated: 2020/11/21 10:36:57 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		dollar_questionmark(t_mini *mini, char **str, int *i)
{
	mini->nbr = ft_itoa(mini->exit_int);
	*str = gnl_strjoin(*str, mini->nbr);
	*i += 2;
}

int			dollar_quote(int *i, char **token, t_mini *mini, char **str)
{
	char	*s;
	int		var_length;

	var_length = 0;
	while ((*token)[(*i) + var_length] != '\0' &&
	(*token)[(*i) + var_length] != '$')
		var_length++;
	s = ft_substr(*token, *i, var_length);
	(*str) = gnl_strjoin((*str), s);
	if (s)
		free(s);
	return (var_length);
}

void		expand_with_pipes(t_mini *mini, int var_length, int j, char **str, int *i)
{
	if (mini->n_quotes % 2 != 0 ||
	(ft_strncmp(mini->pipes_c[mini->cmd].tokens[0], "export", 6) == 0
	&& ft_strlen(mini->pipes_c[mini->cmd].tokens[0]) == 6))
		(*str) = gnl_strjoin((*str), &(mini->env[j][var_length + 1]));
	else
		expand_tokens_pipes(mini, str, *i - 1, &(mini->env[j][var_length + 1]));
}

void		get_env_var(int *i, char **token, t_mini *mini, char **str)
{
	int		var_length;
	int		j;
	char	*s;

	var_length = 0;
	j = 0;
	(*i)++; // for $
	// $"LS"
	if ((*token)[*i] == '"' || (*token)[*i] == '\'')
		var_length = dollar_quote(i, token, mini, str);
	else
	{
		while ((*token)[(*i) + var_length] != '\0' && (ft_isalnum((*token)[(*i)
		+ var_length]) || (*token)[(*i) + var_length] == '_'))
			var_length++;
		while (mini->env[j])
		{
			if (ft_strncmp(&(*token)[(*i)], mini->env[j], var_length) == 0 &&
			mini->env[j][var_length] == '=')
			{
				// if env is "$LS", env remains 1 token
				if (mini->piped == 1)
					expand_with_pipes(mini, var_length, j, str, i);
				else
				{
					if (mini->n_quotes % 2 != 0 ||
					(ft_strncmp(mini->c[mini->cmd].tokens[0], "export", 6) == 0
					&& ft_strlen(mini->c[mini->cmd].tokens[0]) == 6))
						(*str) = gnl_strjoin((*str),
						&(mini->env[j][var_length + 1]));
					else
						expand_tokens(mini, str, *i - 1,
						&(mini->env[j][var_length + 1]));
				}
			}
			j++;
		}
		// if (mini->n_quotes == 0 && *str)
			// free(*str);
		//if not found->trim tokens.
	}
	printf("[%s]left in string\n", *str);
	(*i) += var_length;
	printf("[%d]*i [%d]var_length\n", *i, var_length);
}
