#include "minishell.h"

int		multi_lines(char *str)
{
	int		double_q;
	int		single_q;
	int		i;

	double_q = 0;
	single_q = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\\' && str[i + 1] != '\0')
			i++;
		else if (str[i] == '\'' && (double_q % 2) == 0)
			single_q++;
		else if (str[i] == '"' && (single_q % 2) == 0)
			double_q++;
		i++;
	}
	if ((single_q % 2) == 1 || (double_q % 2) == 1)
		return (1);
	return (0);
}

int check_for_errors(char *s)
{
	int i;

	i = 0;
	if (multi_lines(s))
	{
		ft_putstr_fd("Error:\nMultiline command.\n", 1);
		return (-1);
	}
	while (s[i] != '\0')
	{
		if (s[i] == '\\' && s[i + 1] != '\0')
		{
			i++;
		}
		else if (s[i] == '\\' && s[i + 1] == '\0')
		{
			ft_putstr_fd("Error:\nMultiline command.\n", 1);
			return (-1);
		}
		else if (s[i] == ';' && s[i + 1] == ';')
		{
			ft_putstr_fd("Error:\nSyntax error near ';;'.\n", 1);
			return (-1);
		}
		i++;
	}
	return (0);
}
