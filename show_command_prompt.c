
#include "minishell.h"

void	show_command_prompt(void)
{
	char buf[10000];
	getcwd(buf, 10000);
	ft_putstr_fd("\e[1;33m~", 1);
	ft_putstr_fd(buf, 1);
	ft_putstr_fd("\e[0m", 1);
	write(1, "$ ", 2);
}
