
#include "minishell.h"

// void 	set_env(char *s, t_mini *mini)
// {
// 	int i;

// 	i = 0;
// 	mini->def = ft_strdup(s);
// 	while(s[i] != '=' && s[i] != '\0')
// 		i++;
// 	mini->set = ft_substr(s, 0, i);
// 	mini->alias = ft_strdup(&s[i + 1]);
// 	printf("%s | %s\n", mini->set, mini->alias);
// }

char 	**add_to_env(char *s, t_mini *mini)
{
	char	**new_env;
	int		size;

	size = 0;
	while (mini->env[size])
	{
		size++;
	}
	new_env = ft_calloc(size + 1, sizeof(char *));
	size = 0;
	while (mini->env[size])
	{
		new_env[size] = ft_strdup(mini->env[size]);
		// printf(" ");
		// if (mini->env[size])
			// free(mini->env[size]);
		size++;
	}
	new_env[size] = ft_strdup(s);
	new_env[size + 1] = '\0';
	return (new_env);
}

void	print_export(t_mini *mini)
{
	int i;
	int j;
	int k;
	char *new_str;
	int check;

	i = 0;
	j = 0;
	k = 0;
	check = 0;
	mini->export_env = sort_env(mini->env);
	while (mini->export_env[i])
	{
		ft_putstr_fd("declare -x ", 1);
		new_str = (char *)malloc(sizeof(char) * ft_strlen(mini->export_env[i]) + 3);
		while (mini->export_env[i][j] != '\0')
		{
			new_str[k] = mini->export_env[i][j]; 
			if (mini->export_env[i][j] == '=' && check == 0)
			{
				check = 1;
				k++;
				new_str[k] = '"';
			}
			k++;
			j++;
		}
		check = 0;
		new_str[k] = '"';
		new_str[k + 1] = '\0';
		j = 0;
		k = 0;
		ft_putstr_fd(new_str, 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}

int		check_over_write(char *s, t_mini *mini)
{
	int i;
	int j;
	int len;
	char *str;

	i = 0;
	j = 0;
	while (s[i] != '\0' && s[i] != '=')
		i++;
	str = (char *)malloc(sizeof(char) * i + 1);
	i = 0;
	while (s[i] != '\0' && s[i] != '=')
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	while (mini->env[j])
	{
		len = 0;
		while (mini->env[j][len] != '\0' && mini->env[j][len] != '=')
			len++;
		// printf("i = %i len = %i %s\n", i, len, mini->env[j]);
		if (ft_strncmp(s, mini->env[j], len) == 0 && i == len)
		{
			printf("i = %i len = %i %s | %s\n", i, len, s, mini->env[j]);
			free(mini->env[j]);
			mini->env[j] = ft_strdup(s);
			return (1);
		}
		j++;
	}
	return (0);
}

void	ft_export(char **tokens, int tok_amount, t_mini *mini)
{
	int i;
	int j;

	i = 1;
	j = 0;
	if (tok_amount != 1)
	{
		while (tokens[i][j] != '\0' && tokens[i][j] != '=')
		{
			if (ft_isalnum(tokens[i][j]) == 0)
			{
				ft_putstr_fd("bash: export: ", 1);
				ft_putstr_fd(tokens[i], 1);
				ft_putstr_fd(": not a valid identifier\n", 1);
				return ;
			}
			j++;
		}
	}
	while (tokens[i])
	{
		if (check_over_write(tokens[i], mini) == 0)
			mini->env = add_to_env(tokens[i], mini);
		i++;
	}
	if (i == 1)
		print_export(mini);
	(void)mini;
}
