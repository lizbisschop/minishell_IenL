#include "minishell.h"

void	show_command_prompt(void)
{
	int		i;
	int		j;
	char	*buf;

	i = 31;
	j = 0;
	buf = ft_calloc(4096, sizeof(char));
	getcwd(buf, 4096);
	if (buf[0] == '\0')
		ft_putstr_fd("Error getting path\n", 1);
	ft_putstr_fd("\e[0;31m~", 1);
	while (buf[j] != '\0' && i <= 36)
	{
		ft_putstr_fd("\e[0;", 1);
		ft_putnbr_fd(i, 1);
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
	if (buf[0] != '\0')
		free(buf);
}
