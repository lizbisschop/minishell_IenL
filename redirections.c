/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 18:18:46 by iboeters      #+#    #+#                 */
/*   Updated: 2020/11/22 14:40:07 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	trim_tokens(int i, char ***tokens, int *tok_amount, t_mini *mini)
{
	while ((*tokens)[i])
	{
		free((*tokens)[i]);
		if ((*tokens)[i + 1] != NULL && (*tokens)[i + 2] != NULL)
			(*tokens)[i] = ft_strdup((*tokens)[i + 2]);
		else
		{
			free((*tokens)[i + 1]);
			(*tokens)[i] = NULL;
			(*tokens)[i + 1] = NULL;
		}
		i++;
	}
	*tok_amount -= 2;
}

int		output_redir(int i, char ***tokens, int *tok_amount, t_mini *mini)
{
	(*tokens)[i + 1] = unquote(&((*tokens)[i + 1]), mini);
	if (mini->found_out == 1)
		close(mini->fd);
	mini->found_out = 1;
	if (ft_strlen((*tokens)[i]) == 1)
		mini->fd = open((*tokens)[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		mini->fd = open((*tokens)[i + 1], O_RDWR | O_CREAT | O_APPEND, 0644);
	if (mini->fd == -1)
	{
		err((*tokens)[i + 1], "", 1, mini);
		return (-1);
	}
	trim_tokens(i, tokens, tok_amount, mini);
	return (0);
}

int		input_redir(int i, char ***tokens, int *tok_amount, t_mini *mini)
{
	(*tokens)[i + 1] = unquote(&((*tokens)[i + 1]), mini);
	if (mini->found_in == 1)
		close(mini->fd2);
	mini->found_in = 1;
	mini->fd2 = open(((*tokens)[i + 1]), O_RDONLY);
	if (mini->fd2 == -1)
	{
		err((*tokens)[i + 1], "", 1, mini);
		return (-1);
	}
	trim_tokens(i, tokens, tok_amount, mini);
	return (0);
}

void	set_in_and_out(t_mini *mini)
{
	if (mini->found_out == 1)
	{
		if (mini->piped == 0)
			close(mini->fd_out);
		mini->fd_out = dup(mini->fd);
		close(mini->fd);
		mini->out_redir = 1;
	}
	if (mini->found_in == 1)
	{
		close(mini->fd_in);
		mini->fd_in = dup(mini->fd2);
		close(mini->fd2);
		mini->in_redir = 1;
	}
}

int		check_redir(char ***tokens, int *tok_amount, t_mini *mini)
{
	int		i;
	int		ret;
	int		len;

	i = 0;
	ret = 0;
	mini->found_in = 0;
	mini->found_out = 0;
	mini->out_redir = 0;
	mini->in_redir = 0;
	while ((*tokens)[i])
	{
		len = ft_strlen((*tokens)[i]);
		if ((ft_strncmp((*tokens)[i], ">", 1) == 0 && len == 1)
		|| (ft_strncmp((*tokens)[i], ">>", 2) == 0 && len == 2))
			ret = output_redir(i, tokens, tok_amount, mini);
		else if (ft_strncmp((*tokens)[i], "<", 1) == 0 && len == 1)
			ret = input_redir(i, tokens, tok_amount, mini);
		else
			i++;
		if (ret == -1)
			return (-1);
	}
	set_in_and_out(mini);
	return (0);
}
