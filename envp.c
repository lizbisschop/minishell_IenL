#include "minishell.h"

int	env_command(char **envp, int check)
{
	int i;

	i = 0;
	if (check != 1)
	{
		ft_putstr_fd("Error\n", 1);
		return (-1);
	}
	while (envp[i])
	{
		ft_putstr_fd(envp[i], 1);
		write(1, "\n", 1);
		i++;
	}
	return (0);
}
