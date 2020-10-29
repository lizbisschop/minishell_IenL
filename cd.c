#include "minishell.h"

char	*get_home(t_mini *mini)
{
	char		*home;
	int			i;
	int			j;
	extern char **environ;	

	i = 0;
	j = 0;
	while (mini->env[i])
	{
		if (ft_strncmp("HOME=", mini->env[i], 5) == 0)
		{
			home = ft_strdup(&mini->env[i][5]);
			break ;
		}
		i++;
	}
	if (!mini->env[i])
	{
		while (environ[j])
		{
			if (ft_strncmp("HOME=", environ[j], 5) == 0)
			{
				home = ft_strdup(&environ[j][5]);
				break ;
			}
			j++;
		}
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
		if (home)
			free(home);
		return (-1);
	}
	else if (tok_amount == 1)
		chdir(home);
	else if (tokens[1][0] == '~')
	{
		if (tokens[1][1])
		{
			if (chdir(ft_strjoin(home, &tokens[1][1])) == -1)
			{
				put_error_fd("cd", tokens[1], 1, mini);
				mini->exit_int = 1;
				if (home)
					free(home);
				return (-1);
			}
		}
		else if (chdir(home) == -1)
		{
			put_error_fd("cd", home, 1, mini);
			mini->exit_int = 1;
			if (home)
				free(home);
			return (-1);
		}
	}
	else if (tokens[1][0] == '/' && ft_strlen(tokens[1]) == 1)
		chdir("//");
	else if (ft_strncmp("/root", tokens[1], 5) == 0 &&
	ft_strlen(tokens[1]) == 5)
		chdir("/root");
	else if (chdir(tokens[1]) == -1)
	{
		put_error_fd("cd", tokens[1], 1, mini);
		mini->exit_int = 1;
		if (home)
			free(home);
		return (-1);
	}
	if (home)
		free(home);
	mini->exit_int = 0;
	return (0);
}
