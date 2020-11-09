#include "minishell.h"

void	exec_exit(t_mini *mini, int tok_amount, char **tokens)
{
	int i;

	i = 0;
	if (tok_amount == 1)
	{
		ft_putstr_fd("exit\n", 2);
		exit(0);
	}
	if (tok_amount > 2)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(tokens[1], 2);
		ft_putstr_fd(": too many arguments\n", 2);
		mini->exit_int = 255;
		exit(mini->exit_int);
	}
	while (tokens[1][i] != '\0')
	{
		if (!ft_isdigit(tokens[1][i]))
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(tokens[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			mini->exit_int = 255;
			exit(mini->exit_int);
		}
		i++;
	}
	if (tok_amount == 2)
	{
		ft_putstr_fd("exit\n", 2);
		mini->exit_int = ft_atoi(tokens[1]);
		exit(mini->exit_int);
	}
}
