#include "minishell.h"

void		echo(t_command command)
{
	int		i;
	int		n_flag;

	i = 1;
	n_flag = 0;
	if (command.tok_amount > 1)
	{
		if (ft_strncmp("-n", command.tokens[1], 2) == 0 &&
		ft_strlen(command.tokens[1]) == 2)
		{
			n_flag = 1;
			i++;
		}
		while (i < command.tok_amount)
		{
			// printf("%c|%i|%i\n", command.tokens[i][0], i, command.tok_amount);
			command.tokens[i] = unquote(&command.tokens[i]);
			if (is_delimiter(command.tokens[i][0]))
				break ;
			ft_putstr_fd(command.tokens[i], 1);
			ft_putchar_fd(' ', 1);
			i++;
		}
	}
	if (!n_flag)
		ft_putchar_fd('\n', 1);
}
