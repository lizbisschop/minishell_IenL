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
	struct stat		buf;
	char			*pwd;
	DIR				*dir;
	char			*home;

	err = 0;
	if (!(tokens[0][0] == '.' && tokens[0][1] && tokens[0][1] == '/') &&
	!(tokens[0][0] == '~' && tokens[0][1] && tokens[0][1] == '/') &&
	!(tokens[0][0] == '~' && !tokens[0][1]) &&
	ft_strchr(s, '/') == 0)
	{
		path = get_path(tokens[0]);
		if (path != 0)
		{
			if (tokens[0])
				free(tokens[0]);
			tokens[0] = ft_strdup(path);
			if (s)
				free(s);
			// close(mini->main_out);
			execve(tokens[0], tokens, environ);
		}
		ft_putstr_fd("bash: ", mini->main_out);
		ft_putstr_fd(s, mini->main_out);
		ft_putstr_fd(": command not found\n", mini->main_out);
		close(mini->main_out);
		if (s)
			free(s);
		exit(1);
	}
	else
	{
		if (tokens[0][0] == '~')
		{
			home = get_home(mini);
			if (s[1])
				home = gnl_strjoin(home, &(s[1]));
			if (s)
				free(s);
			s = ft_strdup(home);
			if (tokens[0][1])
			{
				if (tokens[0])
					free(tokens[0]);
				tokens[0] = ft_strdup(s);
			}
			else
			{
				if (tokens[0])
					free(tokens[0]);
				tokens[0] = ft_strdup(s);
			}
		}
		else if (s[0] == '.' && s[1] && s[1] == '/')
		{
			pwd = get_pwd();
			pwd = gnl_strjoin(pwd, "/");
			tokens[0] = gnl_strjoin(pwd, s);
		}
		dir = opendir(tokens[0]);
		if (dir != NULL)
		{
			closedir(dir);
			ft_putstr_fd("bash: ", mini->main_out);
			ft_putstr_fd(s, mini->main_out);
			ft_putstr_fd(": is a directory\n", mini->main_out);
		}
		else if (stat(tokens[0], &buf) != -1)
		{
			// close(mini->main_out);
			if (s)
				free(s);
			execve(tokens[0], tokens, environ);
			ft_putstr_fd("bash: ", mini->main_out);
			ft_putstr_fd(tokens[0], mini->main_out);
			ft_putstr_fd(": ", mini->main_out);
			ft_putstr_fd(strerror(errno), mini->main_out);
			ft_putstr_fd("\n", mini->main_out);
		}
		else
		{
			ft_putstr_fd("bash: ", mini->main_out);
			ft_putstr_fd(s, mini->main_out);
			ft_putstr_fd(": ", mini->main_out);
			ft_putstr_fd(strerror(errno), mini->main_out);
			ft_putstr_fd("\n", mini->main_out);
		}
		close(mini->main_out);
		if (s)
			free(s);
		exit(1);
	}
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
		// if (mini->exit_int != 0 && mini->exit_int != 1)
		// !(ft_strncmp(tokens[0], "exit", 4) && ft_strlen(tokens[0]) == 4))
		// {
		// 	ft_putstr_fd("bash: ", mini->main_out);
		// 	ft_putstr_fd(tokens[0], mini->main_out);
		// 	ft_putstr_fd(": ", mini->main_out);
		// 	ft_putstr_fd(strerror(mini->exit_int), mini->main_out);
		// 	ft_putstr_fd("\n", mini->main_out);
		// 	close(mini->main_out);
		// 	mini->exit_int = 1;
		// }
	}
	if (s)
		free(s);
	return (0);
}
