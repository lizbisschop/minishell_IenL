#include "minishell.h"

void 	check_for_dollar(t_command *command, int *i)
{
	int j;
	int check;

	j = 0;
	check = 0;
	if (command->tokens[*i][0] == '$')
	{
		printf("command = %s", command->tokens[*i]);
		while (__environ[j])
		{
			if (ft_strncmp(&command->tokens[*i][1], __environ[j], ft_strlen(command->tokens[*i]) - 1) == 0)
			{
				command->tokens[*i] = ft_strdup(&__environ[j][ft_strlen(command->tokens[*i]) + 1]);
				check = 1;
			}
			j++;
		}
		if(check == 0)
		{
			command->tokens[*i] = ft_strdup("");
		}
	}
}

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
			if (is_delimiter(command.tokens[i][0]))
				break ;
			// printf("before %s\n", command.tokens[i]);
			command.tokens[i] = unquote(&command.tokens[i]);
			check_for_dollar(&command, &i);
			// printf("after %s\n", command.tokens[i]);
			ft_putstr_fd(command.tokens[i], 1);
			ft_putchar_fd(' ', 1);
			i++;
		}
	}
	if (!n_flag)
		ft_putchar_fd('\n', 1);
}
