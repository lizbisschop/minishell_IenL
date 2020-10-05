#include "minishell.h"

void	handle_signals(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		show_command_prompt();
	}
}

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

int		main(int argc, char **argv)
{
	t_mini mini;

	mini.env = copy_env();
	while (1)
	{
		signal(SIGINT, &handle_signals);
		signal(SIGQUIT, &handle_signals);
		set_struct(&mini);
		show_command_prompt();
		mini.input = read_line();
		if (ft_split_commands(mini.input, &mini) != -1)
		{
			free(mini.input);
			tokens(&mini);
			which_command(&mini);
			free_stuff(&mini);
		}
	}
	(void)argc;
	(void)argv;
	exit(0);
	return (0);
}
