#include "minishell.h"

int		find_command(int cmd, t_mini *mini, char *s, char **envp)
{
	(void)mini;
	if (ft_strncmp("echo", s, 4) == 0 && ft_strlen(s) == 4)
	{
		// if (mini->c[cmd].tok_amount > 1)
		echo(mini->c[cmd]);
	}
	else if (ft_strncmp("pwd", s, 3) == 0 && ft_strlen(s) == 3)
	{
		pwd();
	}
	else if (ft_strncmp("exit", s, 4) == 0 && ft_strlen(s) == 4)
		exit(0);
	else if (ft_strncmp("cd", s, 2) == 0 && ft_strlen(s) == 2)
	{
		cd(mini->c[cmd], mini, envp);
	}
	else if (ft_strncmp("env", s, 3) == 0 && ft_strlen(s) == 3)
	{
		env_command(envp);
	}
	else if (s[0] != '\0')
	{
		ft_putstr_fd("Error:\nCommand: ", 1);
		ft_putstr_fd(s, 1);
		ft_putstr_fd(" not found.\n", 1);
	}
	return (0);
}

void	which_command(t_mini *mini, char **envp)
{
	int		cmd;

	cmd = 0;
	while (cmd < mini->cmds)
	{
		mini->c[cmd].tokens[0] = unquote(&(mini->c[cmd].tokens[0]));
		// printf("unquoted command[%s]\n", mini->c[cmd].tokens[0]);
		if (mini->c[cmd].tok_amount > 0)
			find_command(cmd, mini, mini->c[cmd].tokens[0], envp);
		cmd++;
	}
	(void)envp;
}
