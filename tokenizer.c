/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 18:19:03 by iboeters      #+#    #+#                 */
/*   Updated: 2020/11/22 20:07:50 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		pipe_amount(char **tokens, int tok_amount, t_mini *mini)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	while (i < tok_amount)
	{
		if (ft_strncmp(tokens[i], "|", 1) == 0
		&& ft_strlen(tokens[i]) == 1)
			n++;
		i++;
	}
	if (n > PID_MAX)
	{
		ft_putstr_fd("bash: fork: Resource temporarily unavailable\n", 2);
		mini->exit_int = 128;
		return (-1);
	}
	return (n + 1);
}

int		tok_amount_pipes(char **tokens, int i, int tok_amount)
{
	int		ret;

	ret = 0;
	while (i < tok_amount)
	{
		if (ft_strncmp(tokens[i], "|", 1) == 0
		&& ft_strlen(tokens[i]) == 1)
			return (ret);
		i++;
		ret++;
	}
	return (ret);
}

void	create_tokens_pipes(t_command *cmd, int *i, int *j, char **tokens)
{
	cmd->error_redir = 0;
	cmd->tokens = (char **)malloc((cmd->tok_amount + 1) * sizeof(char *));
	if (!cmd->tokens)
		malloc_error();
	while (*j < cmd->tok_amount)
	{
		cmd->tokens[*j] = ft_strdup(tokens[*i]);
		if (!cmd->tokens[*j])
		{
			ft_putstr_fd("bash: malloc fail\n", 2);
			exit(1);
		}
		(*i)++;
		(*j)++;
	}
	cmd->tokens[*j] = NULL;
	(*i)++;
}

int		tokenizer(char **tokens, int tok_amount, t_mini *mini)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	mini->pipe_cmds = pipe_amount(tokens, tok_amount, mini);
	if (mini->pipe_cmds == -1)
		return (-1);
	mini->pipes_c = (t_command *)malloc(sizeof(t_command) *
	(mini->pipe_cmds + 1));
	if (mini->pipes_c == (void*)-1)
		malloc_error();
	while (k < mini->pipe_cmds)
	{
		j = 0;
		mini->pipes_c[k].invalid_redir = 0;
		mini->pipes_c[k].tok_amount = tok_amount_pipes(tokens, i, tok_amount);
		create_tokens_pipes(&(mini->pipes_c[k]), &i, &j, tokens);
		k++;
	}
	return (0);
}
