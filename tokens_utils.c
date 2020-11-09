#include "minishell.h"

int		ret_del(char *s, int i)
{
	if (s[i] == '>' && s[i + 1] == '>')
		i = i + 2;
	else
		i++;
	return (i);
}
