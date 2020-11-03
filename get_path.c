#include "minishell.h"

char	*get_path_entry(int i, int *j, char *cmd)
{
	int			len;
	extern char **environ;
	char		*str;

	len = 0;
	while (environ[i][*j] != '\0' && environ[i][*j] != ':')
	{
		(*j)++;
		len++;
	}
	str = ft_substr(environ[i], *j - len, len);
	if (cmd[0] != '/')
		str = gnl_strjoin(str, "/");
	str = gnl_strjoin(str, cmd);
	return (str);
}

char	*get_path(char *cmd)
{
	int			i;
	int			j;
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
				str = get_path_entry(i, &j, cmd);
				if (stat(str, &buf) != -1)
					return (str);
				if (str)
					free(str);
				j++;
			}
		}
		i++;
	}
	return (0);
}
