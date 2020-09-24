#include "minishell.h"

char **split_input(char *str)
{
	char **input;
	input = ft_split(str, ';');
	return (input);
}

char	*read_line(void)
{
	char *line;

	line = NULL;
	get_next_line(0, &line);
	return (line);
}