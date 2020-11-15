/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 18:16:06 by iboeters      #+#    #+#                 */
/*   Updated: 2020/11/15 15:21:08 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_home_environ(char **home)
{
	int			j;
	extern char	**environ;

	j = 0;
	while (environ[j])
	{
		if (ft_strncmp("HOME=", environ[j], 5) == 0)
		{
			*home = ft_strdup(&environ[j][5]);
			break ;
		}
		j++;
	}
}

char	*get_home(t_mini *mini)
{
	char		*home;
	int			i;
	extern char **environ;

	i = 0;
	while (mini->env[i])
	{
		if (ft_strncmp("HOME=", mini->env[i], 5) == 0)
		{
			home = ft_strdup(&mini->env[i][5]);
			break ;
		}
		i++;
	}
	if (!mini->env[i])
		check_home_environ(&home);
	if (i == 0)
		return ((void*)0);
	return (home);
}

int		check_tilde(t_mini *mini, char **home, char **tokens)
{
	if (tokens[1][1])
	{
		if (chdir(ft_strjoin(*home, &tokens[1][1])) == -1)
		{
			err("cd: ", tokens[1], 1, mini);
			if (*home)
				free(*home);
			return (-1);
		}
	}
	else if (chdir(*home) == -1)
	{
		err("cd: ", *home, 1, mini);
		if (*home)
			free(*home);
		return (-1);
	}
	if (*home)
		free(*home);
	return (0);
}

int		compare_dot(char **tokens, t_mini *mini, char **home)
{
	mini->pwd = NULL;
	if (ft_strncmp(".", tokens[1], 1) == 0 && ft_strlen(tokens[1]) == 1)
	{
		mini->pwd = get_pwd();
		if (mini->pwd == 0)
		{
			err("cd: ", "", 1, mini);
			if (*home)
				free(*home);
			return (-1);
		}
		mini->pwd = gnl_strjoin(mini->pwd, "/.");
		if (chdir(mini->pwd) == -1)
		{
			err("cd: ", mini->pwd, 1, mini);
			if (*home)
				free(*home);
			if (mini->pwd)
				free(mini->pwd);
			return (-1);
		}
	}
	if (mini->pwd)
		free(mini->pwd);
	return (0);
}

int		cd(char **tokens, int tok_amount, t_mini *mini)
{
	char	*home;

	home = get_home(mini);
	if (tok_amount == 1)
		chdir(home);
	else if (tokens[1][0] == '~')
		return (check_tilde(mini, &home, tokens));
	else if (tokens[1][0] == '/' && ft_strlen(tokens[1]) == 1)
		chdir("//");
	else if (compare_dot(tokens, mini, &home) == -1)
		return (-1);
	else if (chdir(tokens[1]) == -1)
	{
		err("cd: ", tokens[1], 1, mini);
		if (home)
			free(home);
		return (-1);
	}
	if (home)
		free(home);
	mini->exit_int = 0;
	return (0);
}
