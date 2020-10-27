#include "minishell.h"

char	*get_home(t_mini *mini)
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
	if (i == 0)
		return ((void*)0);
	return (home);
}

int		cd(char **tokens, int tok_amount, t_mini *mini)
{
	char	*home;

	home = get_home(mini);
	if (tok_amount > 2)
	{
		ft_putstr_fd("bash: cd: too many arguments\n", 1);
		mini->exit_int = 1;
		return (-1);
	}
	else if (tok_amount == 1)
		chdir(home);
	else if (tokens[1][0] == '~')
		chdir(home);
	else if (tokens[1][0] == '/' && ft_strlen(tokens[1]) == 1)
		chdir("//");
	else if (ft_strncmp("/root", tokens[1], 5) == 0 &&
	ft_strlen(tokens[1]) == 5)
		chdir("/root");
	else if (chdir(tokens[1]) == -1)
	{
		ft_putstr_fd("bash: cd: ", 1);
		ft_putstr_fd(tokens[1], 1);
		ft_putstr_fd(": ", 1);
		ft_putstr_fd(strerror(errno), 1);
		ft_putstr_fd("\n", 1);
		mini->exit_int = 1;
		return (-1);
	}
	if (home)
		free(home);
	mini->exit_int = 0;
	return (0);
}
