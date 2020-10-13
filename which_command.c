#include "minishell.h"

void	exec_exit(t_mini *mini, int cmd)
{
	if (mini->c[cmd].tok_amount != 1)
		ft_putstr_fd("logout\nbash: exit: too many arguments\n", 1);
	else
	{
		free_stuff(mini);
		exit(0);
	}
}

int		find_command(int cmd, t_mini *mini)
{
	int		i;
	char	*s;

	i = 1;
	while (mini->c[cmd].tokens[i])
	{
		check_for_dollar(&(mini->c[cmd].tokens[i]), mini);
		mini->c[cmd].tokens[i] = unquote(&(mini->c[cmd].tokens[i]));
		i++;
	}
	s = ft_strdup(mini->c[cmd].tokens[0]);
	if (ft_strncmp("echo", s, 4) == 0 && ft_strlen(s) == 4)
		echo(mini->c[cmd], mini);
	else if (ft_strncmp("pwd", s, 3) == 0 && ft_strlen(s) == 3)
		pwd();
	else if (ft_strncmp("exit", s, 4) == 0 && ft_strlen(s) == 4)
		exec_exit(mini, cmd);
	else if (ft_strncmp("cd", s, 2) == 0 && ft_strlen(s) == 2)
		cd(mini->c[cmd], mini);
	else if (ft_strncmp("env", s, 3) == 0 && ft_strlen(s) == 3)
		env_command(mini->c[cmd].tok_amount, mini);
	else if (ft_strncmp("export", s, 6) == 0 && ft_strlen(s) == 6)
		ft_export(mini->c[cmd], mini);
	else if (s[0] != '\0')
		exec_cmd(cmd, mini, ft_strdup(mini->c[cmd].tokens[0]));
	if (s)
		free(s);
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
	// int		ret;

	cmd = 0;
	while (cmd < mini->cmds)
	{
		if (any_pipes(mini->c[cmd]))
		{
			printf("pipes aanwezig\n");
			pipes(mini, cmd);
			// ret = fork();
			// if (ret == 0)
			// {
			// }
			// else if (ret == -1)
			// {
			// 	strerror(0);
			// 	return ;
			// }
			// waitpid(ret, NULL, 0);
		}
		else if (mini->c[cmd].tok_amount > 0)
		{
			find_command(cmd, mini);
		}
		cmd++;
	}
}
