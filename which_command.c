#include "minishell.h"

int		find_command(int cmd, t_mini *mini, char *s)
{
	(void)mini;
	if (ft_strncmp("echo", s, 4) == 0 && ft_strlen(s) == 4)
		echo(mini->c[cmd], mini);
	else if (ft_strncmp("pwd", s, 3) == 0 && ft_strlen(s) == 3)
		pwd();
	else if (ft_strncmp("exit", s, 4) == 0 && ft_strlen(s) == 4)
	{
		free_stuff(mini);
		exit(0);
	}
	else if (ft_strncmp("cd", s, 2) == 0 && ft_strlen(s) == 2)
		cd(mini->c[cmd], mini);
	else if (ft_strncmp("env", s, 3) == 0 && ft_strlen(s) == 3)
		env_command(mini->c[cmd].tok_amount, mini);
	else if (ft_strncmp("export", s, 6) == 0 && ft_strlen(s) == 6)
		ft_export(mini->c[cmd], mini);
	else if (s[0] != '\0')
	{
		// printf("hallooo\n");
		exec_cmd(cmd, mini, s);
		// if (exec_cmd(cmd, mini, s) == 1)
		// {
		// 	ft_putstr_fd("Error:\nCommand: ", 1);
		// 	ft_putstr_fd(s, 1);
		// 	ft_putstr_fd(" not found.\n", 1);
		// }
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
		// ret = fork();
		// if (ret == 0)
		// {
			mini->c[cmd].tokens[0] = unquote(&(mini->c[cmd].tokens[0]));
			// printf("%s\n", mini->c[cmd].tokens[0]);
			if (mini->c[cmd].tok_amount > 0)
				find_command(cmd, mini, mini->c[cmd].tokens[0]);
		// }
		// else if (ret == -1)
		// {
			// strerror(0);
			// return ;
		// }
		// waitpid(ret, NULL, 0);
		// printf("unquoted command[%s]\n", mini->c[cmd].tokens[0]);
		cmd++;
	}
}
