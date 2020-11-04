#include "minishell.h"

void		echo(char **tokens, int tok_amount, t_mini *mini)
{
	int		i;
	int		n_flag;

	i = 1;
	n_flag = 0;
	if (tok_amount > 1)
	{
		if (ft_strncmp("-n", tokens[1], 2) == 0 &&
		ft_strlen(tokens[1]) == 2)
		{
			n_flag = 1;
			i++;
		}
		while (i < tok_amount)
		{
			ft_putstr_fd(tokens[i], 1);
			if (i < tok_amount - 1)
				ft_putchar_fd(' ', 1);
			i++;
		}
	}
	if (!n_flag)
		ft_putchar_fd('\n', 1);
	mini->exit_int = 0;
}
