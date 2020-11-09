/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   envp.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 18:16:35 by iboeters      #+#    #+#                 */
/*   Updated: 2020/11/09 18:16:36 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_env(void)
{
	extern char	**environ;
	int			i;
	char		**env;

	i = 0;
	while (environ[i])
		i++;
	env = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (environ[i])
	{
		env[i] = ft_strdup(environ[i]);
		i++;
	}
	env[i] = NULL;
	return (env);
}

int		env_command(int tok_amount, t_mini *mini)
{
	int i;

	i = 0;
	if (tok_amount != 1)
	{
		err("No such file or directory", "", 0, mini);
		mini->exit_int = 127;
		return (-1);
	}
	while (mini->env[i])
	{
		if (ft_strchr(mini->env[i], '='))
		{
			ft_putstr_fd(mini->env[i], 1);
			write(1, "\n", 1);
		}
		i++;
	}
	mini->exit_int = 0;
	return (0);
}
