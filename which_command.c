/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   which_command.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 18:19:20 by iboeters      #+#    #+#                 */
/*   Updated: 2020/11/09 18:19:21 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	var_sub(char **tokens, t_mini *mini)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		check_for_dollar(&(tokens[i]), mini);
		i++;
	}
}

void	find_command(char **tokens, int tok_amount, t_mini *mini)
{
	int		len;

	if (!tokens[0])
		return ;
	len = ft_strlen(tokens[0]);
	quotes(tokens, mini);
	if (ft_strncmp("echo", tokens[0], 4) == 0 && len == 4)
		echo(tokens, tok_amount, mini);
	else if (ft_strncmp("pwd", tokens[0], 3) == 0 && len == 3)
		pwd(mini);
	else if (ft_strncmp("exit", tokens[0], 4) == 0 && len == 4)
		exec_exit(mini, tok_amount, tokens);
	else if (ft_strncmp("cd", tokens[0], 2) == 0 && len == 2)
		cd(tokens, tok_amount, mini);
	else if (ft_strncmp("env", tokens[0], 3) == 0 && len == 3)
		env_command(tok_amount, mini);
	else if (ft_strncmp("export", tokens[0], 6) == 0 && len == 6)
		ft_export(tokens, tok_amount, mini);
	else if (ft_strncmp("unset", tokens[0], 5) == 0 && len == 5)
		unset(tokens, mini);
	else
		exec_cmd(tokens, ft_strdup(tokens[0]), mini);
	if (mini->piped == 1)
		close(mini->main_out);
}

int		any_pipes(t_command cmd)
{
	int i;

	i = 0;
	while (cmd.tokens[i])
	{
		if (ft_strncmp(cmd.tokens[i], "|", 1) == 0
		&& ft_strlen(cmd.tokens[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

void	no_pipes_cmd(int cmd, t_mini *mini)
{
	mini->main_in = dup(STDIN_FILENO);
	mini->main_out = dup(STDOUT_FILENO);
	mini->fd_in = dup(mini->main_in);
	mini->fd_out = dup(mini->main_out);
	mini->c[cmd].invalid_redir = 0;
	mini->c[cmd].error_redir = 0;
	valid_input_redir(&mini->c[cmd], mini);
	if (check_redir(&(mini->c[cmd].tokens), &(mini->c[cmd].tok_amount),
	mini) == -1)
		mini->c[cmd].error_redir = 1;
	dup2(mini->fd_in, STDIN_FILENO);
	dup2(mini->fd_out, STDOUT_FILENO);
	close(mini->fd_in);
	close(mini->fd_out);
	if (mini->c[cmd].invalid_redir != 1 && mini->c[cmd].error_redir != 1)
		find_command(mini->c[cmd].tokens, mini->c[cmd].tok_amount, mini);
	dup2(mini->main_in, STDIN_FILENO);
	dup2(mini->main_out, STDOUT_FILENO);
	close(mini->main_in);
	close(mini->main_out);
}

void	which_command(t_mini *mini)
{
	int		cmd;
	int		j;

	cmd = 0;
	j = 0;
	while (cmd < mini->cmds)
	{
		mini->piped = 0;
		mini->pipe_cmds = 0;
		if (any_pipes(mini->c[cmd]))
		{
			mini->piped = 1;
			if (pipes(mini, cmd) == -1)
				break ;
			free_pipes_c(mini);
		}
		else if (mini->c[cmd].tok_amount > 0)
		{
			var_sub(mini->c[cmd].tokens, mini);
			no_pipes_cmd(cmd, mini);
		}
		cmd++;
	}
}
