#include "minishell.h"

/*
** exit too many arguments
*/

char		*get_path(char *cmd)
{
	int			i;
	int			j;
	int			k;
	char		*str;
	extern char	**environ;
	struct stat	buf;

	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], "PATH=", 5) == 0)
		{
			j = 5;
			while (environ[i][j] != '\0')
			{
				k = 0;
				while (environ[i][j] != '\0' && environ[i][j] != ':')
				{
					j++;
					k++;
				}
				str = ft_substr(environ[i], j - k, k);
				if (cmd[0] != '/')
					str = gnl_strjoin(str, "/");
				str = gnl_strjoin(str, cmd);
				if (stat(str, &buf) != -1)
					return (str);
				j++;
			}
		}
		i++;
	}
	return (0);
}

int			exec_cmd(int cmd, t_mini *mini, char *s)
{
	int			fd[2];
	int			pid;
	extern char **environ;
	int			err;
	char		*path;

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
		path = get_path(mini->c[cmd].tokens[0]);
		if (path != 0)
		{
			mini->c[cmd].tokens[0] = ft_strdup(path);
			err = execve(mini->c[cmd].tokens[0], mini->c[cmd].tokens, environ);
		}
		if (err == -1 || path == 0)
		{
			ft_putstr_fd("bash: ", 1);
			ft_putstr_fd(s, 1);
			ft_putstr_fd(": ", 1);
			ft_putstr_fd("command not found", 1);
			// ft_putstr_fd(strerror(errno), 1);
			ft_putstr_fd("\n", 1);
			if (s)
				free(s);
		}
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
		if (s)
			free(s);
	}
	return (0);
}
