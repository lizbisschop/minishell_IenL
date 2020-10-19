#include "minishell.h"

void	show_command_prompt(void)
{
	int		i;
	int		j;

	i = 31;
	j = 0;
	char buf[4096];
	getcwd(buf, 4096);
	if (buf == NULL)
		ft_putstr_fd("Error getting path\n", 1);
	ft_putstr_fd("\e[0;31m~", 1);
	while (buf[j] != '\0' && i <= 36)
	{
		ft_putstr_fd("\e[0;", 1);
		ft_putstr_fd(ft_itoa(i), 1);
		ft_putstr_fd("m", 1);
		ft_putchar_fd(buf[j], 1);
		if (buf[j] == '/')
			i++;
		if (i == 37)
			i = 31;
		j++;
	}
	ft_putstr_fd("\e[0m", 1);
	write(1, "$ ", 2);
}
