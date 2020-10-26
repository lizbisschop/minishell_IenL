#include "minishell.h"

void	exec_exit(t_mini *mini, int tok_amount)
{
	if (tok_amount != 1)
		ft_putstr_fd("logout\nbash: exit: too many arguments\n", 1);
	else
	{
		free_stuff(mini);
		exit(0);
	}
}

int		find_command(char **tokens, int tok_amount, t_mini *mini)
{
	int		i;
	char	*s;

	i = 1;
	if (!tokens[0])
		return (0);
	while (tokens[i])
	{
		check_for_dollar(&(tokens[i]), mini);
		tokens[i] = unquote(&(tokens[i]), mini);
		i++;
	}
	s = ft_strdup(tokens[0]);
	if (ft_strncmp("echo", s, 4) == 0 && ft_strlen(s) == 4)
		echo(tokens, tok_amount, mini);
	else if (ft_strncmp("pwd", s, 3) == 0 && ft_strlen(s) == 3)
		pwd();
	else if (ft_strncmp("exit", s, 4) == 0 && ft_strlen(s) == 4)
		exec_exit(mini, tok_amount);
	else if (ft_strncmp("cd", s, 2) == 0 && ft_strlen(s) == 2)
		cd(tokens, tok_amount, mini);
	else if (ft_strncmp("env", s, 3) == 0 && ft_strlen(s) == 3)
		env_command(tok_amount, mini);
	else if (ft_strncmp("export", s, 6) == 0 && ft_strlen(s) == 6)
		ft_export(tokens, tok_amount, mini);
	else if (ft_strncmp("unset", s, 5) == 0 && ft_strlen(s) == 5)
		unset(tokens, mini);
	else if (s[0] != '\0')
		exec_cmd(tokens, ft_strdup(tokens[0]), mini);
	if (s)
		free(s);
	if (mini->piped == 1)
		close(mini->main_out);
	return (0);
}

int		any_pipes(t_command com)
{
	int i;

	i = 0;
	while (com.tokens[i])
	{
		if (ft_strncmp(com.tokens[i], "|", 1) == 0
		&& ft_strlen(com.tokens[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

void	which_command(t_mini *mini)
{
	int		cmd;
	int		fd_in;
	int		fd_out;
	int		main_in;
	int		main_out;

	cmd = 0;
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
			main_in = dup(STDIN_FILENO);
			main_out = dup(STDOUT_FILENO);
			mini->main_in = main_in;
			mini->main_out = main_out;
			fd_in = dup(main_in);
			fd_out = dup(main_out);
			check_redir(&fd_out, &fd_in, &(mini->c[cmd].tokens), &(mini->c[cmd].tok_amount), mini);
			dup2(fd_in, STDIN_FILENO);
			dup2(fd_out, STDOUT_FILENO);
			close(fd_in);
			close(fd_out);
			if (valid_input_redir(&mini->c[cmd], mini) != -1)
				find_command(mini->c[cmd].tokens, mini->c[cmd].tok_amount, mini);	
			dup2(main_in, STDIN_FILENO);
			dup2(main_out, STDOUT_FILENO);
			close(main_in);
			close(main_out);
		}
		cmd++;
	}
}
