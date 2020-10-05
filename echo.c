#include "minishell.h"

void 	check_for_dollar(t_command *command, int *i, t_mini *mini)
{
	int		j;
	int		k;
	int		l;
	int		loop;
	int		check;
	char	*str;
	int		save_k;
	int		oohnoo;

	j = 0;
	check = 0;
	l = 0;
	str = (char *)malloc(sizeof(char) * ft_strlen(command->tokens[*i]) + 1);
	k = 0;
	loop = 0;
	oohnoo = 0;
	if ((command->tokens[*i][0] == '"' && ft_strchr(command->tokens[*i], '$')) || command->tokens[*i][0] == '$')
	{
		if (command->tokens[*i][0] == '"')
		{
			k++;
			while (is_whitespace(command->tokens[*i][k]) == 1)
			{
				str[l] = command->tokens[*i][k];
				k++;
				l++;
			}
			if (command->tokens[*i][k] == '$')
			{
				k++;
			}
			str[l] = '\0';
			save_k = k;
			while (is_whitespace(command->tokens[*i][save_k]) == 0 && command->tokens[*i][save_k] != '\0')
			{
				save_k++;
				oohnoo++;
			}
			// printf("%ld, %i, %i, %i\n", ft_strlen(&command->tokens[*i][k]), k, save_k, oohnoo);
			while (mini->env[j])
			{
				if (ft_strncmp(&command->tokens[*i][k], mini->env[j], oohnoo - 1) == 0)
				{
					while (mini->env[j][loop] == command->tokens[*i][k])
					{
						loop++;
						k++;
					}
					str = ft_strjoin(str, &mini->env[j][loop + 1]);
					while (is_whitespace(command->tokens[*i][save_k]) == 1 && command->tokens[*i][save_k] != '\0')
					{
						str = ft_strjoin(str, " ");
						save_k++;
					}
					command->tokens[*i] = ft_strdup(str);
					// printf("token = [%s] string is [%s]\n", command->tokens[*i], str);
				}
				j++;
			}
			check = 1;
		}
		if (command->tokens[*i][0] == '$')
		{
			// printf("command = %s\n", command->tokens[*i]);
			while (mini->env[j])
			{
				if (ft_strncmp(&command->tokens[*i][1], mini->env[j], ft_strlen(command->tokens[*i]) - 1) == 0)
				{
					command->tokens[*i] = ft_strdup(&mini->env[j][ft_strlen(command->tokens[*i])]);
					check = 1;
				}
				j++;
			}
			if(check == 0)
			{
				command->tokens[*i] = ft_strdup("");
			}
		}
	}

}

void		echo(t_command command, t_mini *mini)
{
	int		i;
	int		n_flag;

	i = 1;
	n_flag = 0;
	if (command.tok_amount > 1)
	{
		if (ft_strncmp("-n", command.tokens[1], 2) == 0 &&
		ft_strlen(command.tokens[1]) == 2)
		{
			n_flag = 1;
			i++;
		}
		while (i < command.tok_amount)
		{
			// printf("%c|%i|%i\n", command.tokens[i][0], i, command.tok_amount);
			if (is_delimiter(command.tokens[i][0]))
				break ;
			// printf("before %s\n", command.tokens[i]);
			check_for_dollar(&command, &i, mini);
			command.tokens[i] = unquote(&command.tokens[i]);
			// printf("after %s\n", command.tokens[i]);
			ft_putstr_fd(command.tokens[i], 1);
			ft_putchar_fd(' ', 1);
			i++;
		}
	}
	if (!n_flag)
		ft_putchar_fd('\n', 1);
}
