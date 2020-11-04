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

int			exec_cmd(char **tokens, char *s, t_mini *mini)
{
	int			pid;
	int			wstat;

	if (mini->piped == 1)
		exec_child(tokens, s, mini);
	pid = fork();
	if (pid < 0)
		err(tokens[1], "", 2, mini);
	mini->fd_out = dup(STDOUT_FILENO);
	mini->fd_in = dup(STDIN_FILENO);
	if (pid == 0)
		child_process(tokens, s, mini);
	close(mini->fd_in);
	close(mini->fd_out);
	wait(&wstat);
	if (WIFEXITED(wstat))
		mini->exit_int = WEXITSTATUS(wstat);
	if (s)
		free(s);
	return (0);
}
