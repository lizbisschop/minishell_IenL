#include "minishell.h"

char	*get_input(void)
{
	char *line;

	line = NULL;
	get_next_line(0, &line);
	return (line);
}
