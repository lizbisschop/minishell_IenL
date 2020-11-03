#include "minishell.h"

void	handle_sigint(int signal)
{
	char	*buf;

	buf = ft_calloc(4096, sizeof(char));
	getcwd(buf, 4096);
	if (buf[0] == '\0')
		ft_putstr_fd("Error getting path\n", 2);
	ft_putstr_fd("\n\e[0;33m~", 1); //eruit voor eval
	ft_putstr_fd(buf, 1);
	ft_putstr_fd("\e[0m", 1); //eruit voor eval
	// show_command_prompt();
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

int		main(void)
{
	t_mini	mini;

	mini.env = copy_env();
	mini.exit_int = 0;
	while (1)
	{
		signal(SIGQUIT, &handle_sigquit);
		signal(SIGINT, &handle_sigint);
		set_struct(&mini);
		show_command_prompt();
		mini.input = read_line();

		if (ft_split_commands(mini.input, &mini) != -1)
		{
			printf ("here i am \n");
			tokens(&mini);
			if (multi_line_pipe(&mini) != -1)
				which_command(&mini);
			free_stuff(&mini);
		}
		if (mini.input)
			free(mini.input);
	}
	exit(0);
	return (0);
}
