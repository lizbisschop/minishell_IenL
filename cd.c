#include "minishell.h"

int	cd(t_command command, t_mini *mini)
{
	char	*home;
	int		place;
	int		i;

	place = 0;
	i = 0;
	// skip_whitespaces(str, mini);
	if (command.tok_amount != 2)
	{
		ft_putstr_fd("Error\n", 1);
		return (-1) ;
	}
	command.tokens[1] = unquote(&command.tokens[1]);
	while (command.tokens[1][i])
	{
		i++;
		mini->i++;
	}
	// skip_whitespaces(&str[mini->i], mini);
	if (command.tokens[1][i] != '\0')
	{
		ft_putstr_fd("Error\n Multiple arguments\n", 1);
		return (-1);
	}
	while (__environ[place])
	{
		if (ft_strncmp("HOME=", __environ[place], 5) == 0)
		{
			home = ft_strdup(&__environ[place][5]);
		}
		place++;
	}
	if (command.tokens[1][0] == '~')
	{
		chdir(home);
		mini->i++;
	}
	else if (command.tokens[1][0] == '/' && ft_strlen(command.tokens[1]) == 1)
		chdir("//");
	else if (ft_strncmp("/root", command.tokens[1], 5) == 0 && ft_strlen(command.tokens[1]) == 5)
	{
		// printf("%s\n", word);	
		chdir("/root");
	}
	else
	{
		if (chdir(command.tokens[1]) == -1)
		{
			ft_putstr_fd("bash: ", 1);
			ft_putstr_fd(command.tokens[0], 1);
			ft_putstr_fd(": ", 1);
			ft_putstr_fd(command.tokens[1], 1);			
			ft_putstr_fd(" No such file or directory\n", 1);
		}
	}
	if (home)
		free(home);
	return(0);
}
