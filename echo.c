#include "minishell.h"

/*
** echo $$ = pid van de shell
** export: !isalnum in var name: not a valid identifier
** (otherwise our code also won't work)
** segfault env nadat er een nieuwe var is gezet
** exit: 1 2 3: multiple numbers = too many arguments, otherwise just exit.
** export can only take letters int the part before '='
*/

void		get_env_var(int *i, char **token, t_mini *mini, char **str)
{
	int		var_length;
	int		j;

	var_length = 0;
	j = 0;
	(*i)++;
	printf("%c\n", (*token)[*i]);
	if ((*token)[*i] == '_')
	{
		printf("i am here\n");
		*token = ft_strdup("");
		return ;
	}
	while ((*token)[(*i) + var_length] != '\0' && ft_isalnum((*token)[(*i) +
	var_length]))
		var_length++;
	while (mini->env[j])
	{
		if (ft_strncmp(&(*token)[(*i)], mini->env[j], var_length) == 0)
		{
			(*str) = gnl_strjoin((*str), &(mini->env[j][var_length + 1]));
		}
		j++;
	}
	(*i) += var_length;
}

void		set_open_q(char token, char *q, int *n_quotes)
{
	char	anti_q;
	char	temp;

	if (q[0] == '\'')
		anti_q = '"';
	else
		anti_q = '\'';
	if (token == q[0])
		(*n_quotes)++;
	else if (token == anti_q && (*n_quotes) % 2 == 0)
	{
		(*n_quotes)++;
		temp = q[0];
		q[0] = anti_q;
		anti_q = temp;
	}
}

void		check_for_dollar(char **token, t_mini *mini)
{
	int		i;
	char	*str;
	char	c[2];
	char	q;
	int		n_quotes;

	i = 0;
	str = ft_strdup("");
	q = '"';
	n_quotes = 0;
	if (ft_strchr(*token, '$'))
	{
		while ((*token)[i] != '\0')
		{
			set_open_q((*token)[i], &q, &n_quotes);
			printf("%c | %s\n", q, *token);
			if ((*token)[i] == '$' && (*token)[i + 1] == '?' && q != '\'')
			{
				printf("hellllo\n");
				str = gnl_strjoin(str, ft_itoa(mini->exit_int));
				i += 2;
			}
			if ((*token)[i] == '$' && q != '\'')
				get_env_var(&i, token, mini, &str);
			else
			{
				c[0] = (*token)[i];
				c[1] = '\0';
				str = gnl_strjoin(str, c);
				i++;
			}
		}
		(*token) = ft_strdup(str);
		if (str)
			free(str);
	}
}

void		echo(char **tokens, int tok_amount, t_mini *mini)
{
	int		i;
	int		n_flag;

	i = 1;
	n_flag = 0;
	ft_putstr_fd("", mini->main_out);
	if (tok_amount > 1)
	{
		if (ft_strncmp("-n", tokens[1], 2) == 0 &&
		ft_strlen(tokens[1]) == 2)
		{
			n_flag = 1;
			i++;
		}
		while (i < tok_amount)
		{
			// printf("%c|%i|%i\n", tokens[i][0], i, tok_amount);
			// if (is_delimiter(tokens[i][0]))
			// 	break ;
			ft_putstr_fd(tokens[i], 1);
			if (i < tok_amount -1)
				ft_putchar_fd(' ', 1);
			i++;
		}
	}
	if (!n_flag)
		ft_putchar_fd('\n', 1);
	mini->exit_int = 0;
}
