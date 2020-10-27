#include "minishell.h"

void	pwd(t_mini *mini)
{
	char buf[4096];

	getcwd(buf, 4096);
	ft_putstr_fd(buf, 1);
	write(1, "\n", 1);
	mini->exit_int = 0;
}
