#include "minishell.h"

void	pwd(void)
{
	char buf[10000];
	getcwd(buf, 10000);
	if (buf == NULL)
	{
		ft_putstr_fd("Error\n", 1);
		return ;
	}
	ft_putstr_fd(buf, 1);
	write(1, "\n", 1);
}