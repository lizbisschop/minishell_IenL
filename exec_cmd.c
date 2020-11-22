/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_cmd.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 18:16:45 by iboeters      #+#    #+#                 */
/*   Updated: 2020/11/22 15:43:43 by lbisscho      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		child_process(char **tokens, char *s, t_mini *mini)
{
	close(mini->main_in);
	dup2(mini->fd_out, STDOUT_FILENO);
	close(mini->fd_out);
	dup2(mini->fd_in, STDIN_FILENO);
	close(mini->fd_in);
	exec_child(tokens, s, mini);
}

void		exec_cmd(char **tokens, char *s, t_mini *mini)
{
	int			pid;
	int			wstat;

	if (mini->piped == 1)
		exec_child(tokens, s, mini);
	pid = fork();
	if (pid < 0)
	{
		err("Forking went wrong", "", 1, mini);
		return ;
	}
	mini->fd_out = dup(STDOUT_FILENO);
	mini->fd_in = dup(STDIN_FILENO);
	if (pid == 0)
		child_process(tokens, s, mini);
	close(mini->fd_in);
	close(mini->fd_out);
	if (mini->input != NULL)
		signal_child();
	wait(&wstat);
	if (WIFEXITED(wstat))
		mini->exit_int = WEXITSTATUS(wstat);
	if (s)
		free(s);
}
