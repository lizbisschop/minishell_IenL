#include "minishell.h"

int	cd(char *str, t_mini *mini, char **envp)
{
	char	*home;
	int		place;
	char	*word;
	int		i;

	place = 0;
	i = 0;
	skip_whitespaces(str, mini);
	word = unquote(&str[mini->i], mini, 0);
	while (word[i])
	{
		i++;
		mini->i++;
	}
	skip_whitespaces(&str[mini->i], mini);
	if (str[mini->i] != '\0')
	{
		ft_putstr_fd("Error\n Multiple arguments\n", 1);
		return (-1);
	}
	while (envp[place])
	{
		if (ft_strncmp("HOME=", envp[place], 5) == 0)
		{
			home = ft_strdup(&envp[place][5]);
		}
		place++;
	}
	if (word[0] == '~')
	{
		chdir(home);
		mini->i++;
	}
	else if (word[0] == '/' && ft_strlen(word) == 1)
		chdir("//");
	else if (ft_strncmp("/root", word, 5) == 0 && ft_strlen(word) == 5)
	{
		printf("%s\n", word);	
		chdir("/root");
	}
	else
	{
		if (chdir(word) == -1)
		{
			ft_putstr_fd("bash: ", 1);
			ft_putstr_fd(mini->command, 1);
			ft_putstr_fd(": ", 1);
			ft_putstr_fd(word, 1);			
			ft_putstr_fd(" No such file or directory\n", 1);
		}
	}
	return(0);
}
