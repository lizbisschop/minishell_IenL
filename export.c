#include "minishell.h"

void	print_export(t_mini *mini)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	mini->check_export = 0;
	mini->export_env = sort_env(mini->env, mini);
	while (mini->export_env[i])
	{
		ft_putstr_fd("declare -x ", 1);
		mini->export_str = (char *)malloc(sizeof(char)
		* ft_strlen(mini->export_env[i]) + 3);
		find_right_env(mini, &i, &j, &k);
		if_quote(&k, &j, mini);
		i++;
	}
	free_env_export(mini);
}

int		loop_env(t_mini *mini, char **str, char *s, int *i)
{
	int len;
	int j;

	j = 0;
	len = 0;
	while (mini->env[j])
	{
		len = 0;
		while (mini->env[j][len] != '\0' && mini->env[j][len] != '=')
			len++;
		if (ft_strncmp(s, mini->env[j], len) == 0 && *i == len)
		{
			if (mini->env[j])
				free(mini->env[j]);
			mini->env[j] = ft_strdup(s);
			if (*str)
				free(*str);
			return (1);
		}
		j++;
	}
}

int		check_over_write(char *s, t_mini *mini)
{
	int		i;
	int		j;
	int		len;
	char	*str;

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
	if (loop_env(mini, &str, s, &i) == 1)
		return (1);
	if (str)
		free(str);
	return (0);
}

int		correct_export(char **tokens, t_mini *mini)
{
	int i;

	i = 1;
	while (tokens[i])
	{
		if (tokens[i][0] == '=')
			err("export: `=' not a valid identifier", "", 0, mini);
		if (check_over_write(tokens[i], mini) == 0)
			mini->env = add_to_env(tokens[i], mini);
		i++;
	}
	if (i == 1)
		print_export(mini);
}

void	ft_export(char **tokens, int tok_amount, t_mini *mini)
{
	int i;
	int j;

	i = 1;
	j = 0;
	if (tok_amount != 1)
	{
		printf("im in here\n");
		printf("%s\n", tokens[i]);
		printf("%c\n", tokens[i][j]);
		while (tokens[i][j] != '\0' && tokens[i][j] != '=')
		{
			if (!ft_isalnum(tokens[i][j]))
			{
				ft_putstr_fd("bash: export:", 2);
				ft_putstr_fd(tokens[i], 2);
				ft_putstr_fd(" not a valid identifier\n", 2);
				mini->exit_int = 1;
				return ;
			}
			j++;
		}
	}
	correct_export(tokens, mini);
	mini->exit_int = 0;
}
