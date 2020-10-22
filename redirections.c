#include "minishell.h"

// int			check_output_redir(char **tokens, int tok_amount)
// {
// 	int		i;

// 	while (i)
// }

void		trim_tokens(int i, char ***tokens)
{
	while ((*tokens)[i])
	{
		free((*tokens)[i]);
		if ((*tokens)[i + 1] != NULL && (*tokens)[i + 2] != NULL)
			(*tokens)[i] = ft_strdup((*tokens)[i + 2]);
		else
		{
			free((*tokens)[i + 1]);
			(*tokens)[i] = NULL;
			(*tokens)[i + 1] = NULL;
		}
		i++;
	}
	i = 0;
	printf("trimmed tokens\n");
	while ((*tokens)[i])
	{
		printf("[%s]\n", (*tokens)[i]);
		i++;
	}
}

int			check_input_redir(int *fd_in, char ***tokens)
{
	int		i;
	int		fd;
	int		found;

	found = 0;
	i = 0;
	while ((*tokens)[i])
	{
		if (ft_strncmp((*tokens)[i], "<", 1) == 0 &&
		ft_strlen((*tokens)[i]) == 1)
		{
			if (found == 1)
				close(fd);
			found = 1;
			fd = open((*tokens)[i + 1], O_RDONLY);
			if (fd == -1)
			{
				ft_putstr_fd("bash: ", 1);
				ft_putstr_fd((*tokens)[i + 1], 1);
				ft_putstr_fd(": No such file or directory\n", 1);
				return (-1);
			}
			trim_tokens(i, tokens);
		}
		else
			i++;
	}
	if (found == 1)
	{
		*fd_in = dup(fd);
		close(fd);
		return (1);
	}
	return (0);
}
