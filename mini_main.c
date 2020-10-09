#include "minishell.h"

void	handle_sigint(int signal)
{
	ft_putchar_fd('\n', 1);
	show_command_prompt();
	g_prompt = 0;
	(void)signal;
}

void	handle_sigquit(int signal)
{
	(void)signal;
}

void	set_struct(t_mini *mini)
{
	mini->i = 0;
	mini->cmds = 0;
	mini->end_string = 0;
	mini->slash = 0;
	mini->end = 0;
}

int		main(int argc, char **argv)
{
	t_mini	mini;

	mini.env = copy_env();
	while (1)
	{
		g_prompt = 1;
		signal(SIGINT, &handle_sigint);
		signal(SIGQUIT, &handle_sigquit);
		set_struct(&mini);
		if (g_prompt == 1)
		{
			show_command_prompt();
		}
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
