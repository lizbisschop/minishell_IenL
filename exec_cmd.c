#include "minishell.h"

/*
** unquote tokens before executing
*/

int			exec_cmd(int cmd, t_mini *mini, char *s)
{
	int			fd[2];
	int			pid;
	int			i;
	extern char **environ;
	int			err;

	i = 0;
	if (pipe(fd) == -1)
	{
		printf("Pipe not constructed\n");
		return (1);
	}
	pid = fork();
	// printf("pid[%d]\n", pid);
	if (pid < 0)
		return (1);
	if (pid == 0)
	{
		//Child process
		close(fd[0]);
		// int fd3 = open("file.txt", O_RDWR, 0777);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		mini->c[cmd].tokens[0] = ft_strjoin_read("/bin/", mini->c[cmd].tokens[0]);
		err = execve(mini->c[cmd].tokens[0], mini->c[cmd].tokens, environ);
		if (err == -1)
			printf("Execve did not work\n");
		exit(1);
	}
	else
	{
		//Parent process
		char buf[100 + 1];
		int ret;

		ret = 1;
		close(fd[1]);
		while (ret > 0)
		{
			ret = read(fd[0], &buf, 100);
			buf[ret] = '\0';
			if (ret > 0)
				ft_putstr_fd(buf, 1);
		}
		close(fd[0]);
		wait(NULL);
	}
	return (0);
}
