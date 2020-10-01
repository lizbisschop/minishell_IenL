#include "minishell.h"

int	env_command(int check)
{
	int i;

	i = 0;
	if (check != 1)
	{
		ft_putstr_fd("Error\n", 1);
		return (-1);
	}
	while (__environ[i])
	{
		ft_putstr_fd(__environ[i], 1);
		write(1, "\n", 1);
		i++;
	}
	return (0);
}
