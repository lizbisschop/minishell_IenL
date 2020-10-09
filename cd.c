#include "minishell.h"

int	cd(t_command command, t_mini *mini)
{
	char	*home;
	int		i;

	i = 0;
	while (mini->env[i])
	{
		if (ft_strncmp("HOME=", mini->env[i], 5) == 0)
		{
			home = ft_strdup(&mini->env[i][5]);
			break ;
		}
		i++;
	}
	if (command.tok_amount > 2)
		ft_putstr_fd("bash: cd: too many arguments\n", 1);
	else if (command.tok_amount == 1)
		chdir(home);
	else if (command.tokens[1][0] == '~')
		chdir(home);
	else if (command.tokens[1][0] == '/' && ft_strlen(command.tokens[1]) == 1)
		chdir("//");
	else if (ft_strncmp("/root", command.tokens[1], 5) == 0 &&
	ft_strlen(command.tokens[1]) == 5)
		chdir("/root");
	else
	{
		if (chdir(command.tokens[1]) == -1)
		{
			ft_putstr_fd("bash: cd: ", 1);
			ft_putstr_fd(command.tokens[1], 1);
			ft_putstr_fd(": No such file or directory\n", 1);
		}
	}
	if (home)
		free(home);
	return (0);
}
