#include "minishell.h"

void	handle_sigint(int signal)
{
	ft_putchar_fd('\n', 1);
	show_command_prompt();
	(void)signal;
}

void	handle_sigquit(int signal)
{
	(void)signal;
}

void	set_struct(t_mini *mini)
{
	mini->cmds = 0;
	mini->end = 0;
	mini->in_redir = 0;
	mini->out_redir = 0;
	mini->c = (void*)(0);
}

int		main(int argc, char **argv)
{
	t_mini	mini;

	mini.env = copy_env();
	while (1)
	{
		signal(SIGINT, &handle_sigint);
		signal(SIGQUIT, &handle_sigquit);
		set_struct(&mini);
		show_command_prompt();
		mini.input = read_line();
		if (ft_split_commands(mini.input, &mini) != -1)
		{
			free(mini.input);
			tokens(&mini);
			if (multi_line_pipe(&mini) != -1)
				which_command(&mini);
		}
		free_stuff(&mini);
	}
	(void)argc;
	(void)argv;
	exit(0);
	return (0);
}
