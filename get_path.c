/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_path.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 18:18:09 by iboeters      #+#    #+#                 */
/*   Updated: 2020/11/09 18:18:10 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path_entry(int i, int *j, char *cmd, t_mini *mini)
{
	int			len;
	char		*str;

	len = 0;
	while (mini->env[i][*j] != '\0' && mini->env[i][*j] != ':')
	{
		(*j)++;
		len++;
	}
	str = ft_substr(mini->env[i], *j - len, len);
	if (cmd[0] != '/')
		str = gnl_strjoin(str, "/");
	str = gnl_strjoin(str, cmd);
	return (str);
}

char	*get_path(char *cmd, t_mini *mini)
{
	int			i;
	int			j;
	char		*str;
	struct stat	buf;

	i = 0;
	while (mini->env[i])
	{
		if (ft_strncmp(mini->env[i], "PATH=", 5) == 0)
		{
			j = 5;
			while (mini->env[i][j] != '\0')
			{
				str = get_path_entry(i, &j, cmd, mini);
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
