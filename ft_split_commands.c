#include "minishell.h"

/*
**	; tussen quotes worden gezien als nieuw command: echo "hoi; echo hee"
**	\ within quotes laten staan: verliest zijn functie: echo "\hoi"
**	\ laten staan voor quotes: \"echo \"hoi: bij tokenizen al fout
**		-> of direct unquoten al? bij tokenizen
*/

int		command_count(char *s)
{
	int i;
	int semicolon;
	int	empty;

	i = 0;
	semicolon = 0;
	empty = 1;
	while (s[i] != '\0')
	{
		if (empty == 1 && (!((s[i] >= 9 && s[i] <= 12) || s[i] == 32
		|| s[i] == ';') || (s[i] == '\\' && s[i + 1] == '\\')))
			empty = 0;
		if (s[i] == '"')
		{
			i++;
			while (s[i] != '"' && s[i] != '\0')
				i++;
		}
		else if (s[i] == '\'')
		{
			i++;
			while (s[i] != '\'' && s[i] != '\0')
				i++;
		}
		else if (s[i] == '\\' && s[i + 1] != '\0')
		{
			empty = 0;
			i++;
		}
		else if (s[i] == ';' && empty == 0)
		{
			// printf("|%s|\n", &s[i]);
			semicolon++;
			empty = 1;
		}
		i++;
	}
	if (empty == 1)
		semicolon--;
	return (semicolon + 1);
}

int		len_str(char *s, int begin, int check)
{
	int		str_len;

	str_len = 0;
	while (s[begin] != '\0' && begin < check)
	{
		if (s[begin] == '"')
		{
			begin++;
			str_len++;
			while (s[begin] != '"' && s[begin] != '\0')
			{
				begin++;
				str_len++;
				if (s[begin] == '\\' && (s[begin + 1] == '"'))
					begin++;
				else
				{
					str_len++;
					begin++;
				}
			}
		}
		if (s[begin] == '\\')
			begin++;
		str_len++;
		begin++;
	}
	return (str_len);
}

int		find_substr(char *s, t_mini *mini)
{
	int	empty;

	empty = 1;
	while (s[mini->end] != '\0')
	{
		if (empty == 1 && (!((s[mini->end] >= 9 && s[mini->end] <= 12) || s[mini->end] == 32
		|| s[mini->end] == ';') || (s[mini->end] == '\\' && s[mini->end + 1] == '\\')))
			empty = 0;
		if (s[mini->end] == '"')
		{
			mini->end++;
			while (s[mini->end] != '"' && s[mini->end] != '\0')
				mini->end++;
		}
		else if (s[mini->end] == '\'')
		{
			mini->end++;
			while (s[mini->end] != '\'' && s[mini->end] != '\0')
				mini->end++;
		}
		else if (s[mini->end] == '\\' && s[mini->end + 1] != '\0')
		{
			empty = 0;
			mini->end++;
		}
		else if (s[mini->end] == ';' && empty == 0)
			return (1);
		else if (s[mini->end] == ';' && empty == 1)
			return (0);
		mini->end++;
	}
	if (empty == 1)
		return (0);
	return (1);
}

int 	save_commands(t_mini *mini, char *s)
{
	int command;
	int i;
	int ret;

	command = 0;
	i = 0;
	while (command < mini->cmds)
	{
		ret = 0;
		while (ret == 0)
		{
			ret = find_substr(s, mini);
			if (ret == 1)
			{
				mini->sp_input[command] = ft_substr(s, i, mini->end - i);
				if (!mini->sp_input[command])
				{
					err("bash: malloc has failed", "", 2, mini);
					return (-1);
				}
			}
			mini->end++;
			i = mini->end;
		}
		i = mini->end;
		command++;
	}
	mini->sp_input[command] = NULL;
	return (0);
}

int		ft_split_commands(char *s, t_mini *mini)
{
	mini->cmds = command_count(s);
	mini->sp_input = (char **)malloc(sizeof(char *) * (mini->cmds + 1));
	if (!mini->sp_input)
	{
		err("bash: malloc has failed", "", 2, mini);
		return (-1);
	}
	if (check_for_errors(s, mini) == -1)
	{
		if (mini->sp_input)
			free(mini->sp_input);
		return (-1);
	}
	if (save_commands(mini, s) == -1)
		return (-1);
	return (0);
}
