#include "minishell.h"

void	exec_exit(t_mini *mini, int tok_amount, char **tokens)
{
	if (tok_amount > 1)
	{
		mini->exit_int = ft_atoi(tokens[1]);
		exit(mini->exit_int);
	}
	else
		exit(0);
}
