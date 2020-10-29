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

int	env_command(int check, t_mini *mini)
{
	int i;

	i = 0;
	if (check != 1)
	{
		ft_putstr_fd("bash: e\n", 1);
		mini->exit_int = 1;
		return (-1);
	}
	while (mini->env[i])
	{
		ft_putstr_fd(mini->env[i], 1);
		write(1, "\n", 1);
		i++;
	}
	mini->exit_int = 0;
	return (0);
}
