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
		ft_putstr_fd("Error getting path\n", 2);
	ft_putstr_fd("\e[0;33m~", 1); //eruit voor eval
	ft_putstr_fd(buf, 1);
	ft_putstr_fd("\e[0m", 1); //eruit voor eval
	write(1, "$ ", 2);
	if (buf[0] != '\0')
		free(buf);
}
