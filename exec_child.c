/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_child.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 18:16:40 by iboeters      #+#    #+#                 */
/*   Updated: 2020/11/09 18:16:41 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_executable(char ***tokens, char **s, t_mini *mini)
{
	char			*path;
	extern char		**environ;

	path = get_path((*tokens)[0], mini);
	if (path != 0 && ft_strlen((*tokens)[0]))
	{
		if ((*tokens)[0])
			free((*tokens)[0]);
		(*tokens)[0] = ft_strdup(path);
		if (*s)
			free(*s);
		close(mini->main_out);
		execve((*tokens)[0], (*tokens), environ);
		err((*tokens)[0], "", 1, mini);
		exit(1);
	}
	err(*s, ": command not found", 0, mini);
	close(mini->main_out);
	if (*s)
		free(*s);
	exit(127);
}

void	substitute_token(char ***tokens, char **s, t_mini *mini)
{
	char	*home;
	char	*pwd;

	if ((*tokens)[0][0] == '~')
	{
		home = get_home(mini);
		if ((*s)[1])
			home = gnl_strjoin(home, s[1]);
		if (*s)
			free(*s);
		*s = ft_strdup(home);
		if ((*tokens)[0])
			free((*tokens)[0]);
		(*tokens)[0] = ft_strdup(*s);
	}
	else if ((*s)[0] == '.' && (*s)[1] && (*s)[1] == '/')
	{
		pwd = get_pwd();
		pwd = gnl_strjoin(pwd, "/");
		(*tokens)[0] = gnl_strjoin(pwd, *s);
	}
}

void	close_and_free(t_mini *mini, char **s)
{
	close(mini->main_out);
	if (*s)
		free(*s);
}

void	check_dir_and_exec(char ***tokens, char **s, t_mini *mini)
{
	struct stat		buf;
	DIR				*dir;
	extern char		**environ;

	dir = opendir((*tokens)[0]);
	if (dir != NULL)
	{
		closedir(dir);
		err(*s, ": is a directory", 0, mini);
		close_and_free(mini, s);
		exit(126);
	}
	else if (stat((*tokens)[0], &buf) != -1)
	{
		close_and_free(mini, s);
		execve((*tokens)[0], (*tokens), environ);
		err(*s, "", 1, mini);
		exit(126);
	}
	else
	{
		err(*s, "", 1, mini);
		close_and_free(mini, s);
		exit(127);
	}
}

int		exec_child(char **tokens, char *s, t_mini *mini)
{
	extern char		**environ;

	if (!(tokens[0][0] == '.' && tokens[0][1] && tokens[0][1] == '/') &&
	!(tokens[0][0] == '~' && tokens[0][1] && tokens[0][1] == '/') &&
	!(tokens[0][0] == '~' && !tokens[0][1]) &&
	ft_strchr(s, '/') == 0)
		find_executable(&tokens, &s, mini);
	else
	{
		substitute_token(&tokens, &s, mini);
		check_dir_and_exec(&tokens, &s, mini);
		close(mini->main_out);
		if (s)
			free(s);
		exit(1);
	}
	return (0);
}
