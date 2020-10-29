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

int			exec_child(char **tokens, char *s, t_mini *mini)
{
	char			*path;
	int				err;
	extern char		**environ;

	err = 0;
	path = get_path(tokens[0]);
	if (path != 0)
	{
		if (tokens[0])
			free(tokens[0]);
		tokens[0] = ft_strdup(path);
		close(mini->main_out);
		err = execve(tokens[0], tokens, environ);
	}
	if (err == -1)
	{
		if (s)
			free(s);
		exit(2);
	}
	ft_putstr_fd("bash: ", mini->main_out);
	ft_putstr_fd(s, mini->main_out);
	ft_putstr_fd(": command not found\n", mini->main_out);
	close(mini->main_out);
	if (s)
		free(s);
	exit(1);
}

int			exec_cmd(char **tokens, char *s, t_mini *mini)
{
	int			pid;
	int			fd_out;
	int			fd_in;
	int			wstat;

	if (mini->piped == 1)
		exec_child(tokens, s, mini);
	pid = fork();
	if (pid < 0)
		return (1);
	fd_out = dup(STDOUT_FILENO);
	fd_in = dup(STDIN_FILENO);
	if (pid == 0)
	{
		close(mini->main_in);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
		exec_child(tokens, s, mini);
	}
	close(fd_in);
	close(fd_out);
	wait(&wstat);
	if (WIFEXITED(wstat)) //if normal termination
	{
		mini->exit_int = WEXITSTATUS(wstat);
		if (mini->exit_int == 2)
		{
			mini->exit_int = 1;
			ft_putstr_fd("bash: ", mini->main_out);
			ft_putstr_fd(s, mini->main_out);
			ft_putstr_fd(": ", mini->main_out);
			ft_putstr_fd(strerror(errno), mini->main_out); // stderr needs to be redirected
			ft_putstr_fd("\n", mini->main_out);
		}
	}
	if (s)
		free(s);
	return (0);
}
