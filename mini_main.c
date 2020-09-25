#include "minishell.h"

void	set_struct(t_mini *mini)
{
	mini->i = 0;
	mini->cmds = 0;
	mini->end_string = 0;
	mini->slash = 0;
	mini->end = 0;
}

char	*read_line(void)
{
	char *line;

	line = NULL;
	get_next_line(0, &line);
	return (line);
}

int		main(int argc, char **argv, char **envp)
{
	t_mini mini;

	while (1)
	{
		set_struct(&mini);
		show_command_prompt();
		mini.input = read_line();
		ft_split_commands(mini.input, &mini);
		tokens(&mini);
		which_command(&mini, envp);
	}
	(void)argc;
	(void)argv;
	(void)envp;
	exit(0);
	return (0);
}
