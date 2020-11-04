#include "minishell.h"

void	exec_exit(t_mini *mini, int tok_amount, char **tokens)
{
	if (tok_amount > 1)
	{
		mini->exit_int = ft_atoi(tokens[1]);
		exit(mini->exit_int);
	}
	else
		exit(0);
}

void	var_sub_and_unquote(char **tokens, t_mini *mini)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (i != 0)
		{
			check_for_dollar(&(tokens[i]), mini);
		}
		tokens[i] = unquote(&(tokens[i]), mini);
		i++;
	}
}

int		find_command(char **tokens, int tok_amount, t_mini *mini)
{
	char	*s;

	if (!tokens[0])
		return (0);
	if (mini->piped == 1)
		var_sub_and_unquote(tokens, mini);
	s = ft_strdup(tokens[0]);
	if (ft_strncmp("echo", s, 4) == 0 && ft_strlen(s) == 4)
		echo(tokens, tok_amount, mini);
	else if (ft_strncmp("pwd", s, 3) == 0 && ft_strlen(s) == 3)
		pwd(mini);
	else if (ft_strncmp("exit", s, 4) == 0 && ft_strlen(s) == 4)
		exec_exit(mini, tok_amount, tokens);
	else if (ft_strncmp("cd", s, 2) == 0 && ft_strlen(s) == 2)
		cd(tokens, tok_amount, mini);
	else if (ft_strncmp("env", s, 3) == 0 && ft_strlen(s) == 3)
		env_command(tok_amount, mini);
	else if (ft_strncmp("export", s, 6) == 0 && ft_strlen(s) == 6)
		ft_export(tokens, tok_amount, mini);
	else if (ft_strncmp("unset", s, 5) == 0 && ft_strlen(s) == 5)
		unset(tokens, mini);
	else
		exec_cmd(tokens, ft_strdup(tokens[0]), mini);
	if (s)
		free(s);
	if (mini->piped == 1)
		close(mini->main_out);
	return (0);
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
			pipes(mini, cmd);
		}
		else if (mini->c[cmd].tok_amount > 0)
		{
			var_sub_and_unquote(mini->c[cmd].tokens, mini);
			mini->main_in = dup(STDIN_FILENO);
			mini->main_out = dup(STDOUT_FILENO);
			mini->fd_in = dup(mini->main_in);
			mini->fd_out = dup(mini->main_out);
			mini->c[cmd].invalid_input = 0;
			valid_input_redir(&mini->c[cmd], mini);
			check_redir(&(mini->c[cmd].tokens), &(mini->c[cmd].tok_amount),
			mini);
			dup2(mini->fd_in, STDIN_FILENO);
			dup2(mini->fd_out, STDOUT_FILENO);
			close(mini->fd_in);
			close(mini->fd_out);
			if (mini->c[cmd].invalid_input != 1)
				find_command(mini->c[cmd].tokens, mini->c[cmd].tok_amount, mini);
			dup2(mini->main_in, STDIN_FILENO);
			dup2(mini->main_out, STDOUT_FILENO);
			close(mini->main_in);
			close(mini->main_out);
		}
		cmd++;
	}
}
