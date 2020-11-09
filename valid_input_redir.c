#include "minishell.h"

int		valid_input_redir(t_command *command, t_mini *mini)
{
	int i;
	int	fd;

	i = 0;
	while (command->tokens[i])
	{
		if (ft_strncmp(command->tokens[i], "<", 1) == 0 &&
		ft_strlen(command->tokens[i]) == 1)
		{
			if (command->tokens[i + 1])
				fd = open(command->tokens[i + 1], O_RDONLY);
			if (!command->tokens[i + 1] || fd == -1)
			{
				if (fd == -1)
					err(command->tokens[i + 1], "", 1, mini);
				mini->exit_int = 1;
				command->invalid_redir = 1;
				return (-1);
			}
			close(fd);
		}
		i++;
	}
	return (0);
}
