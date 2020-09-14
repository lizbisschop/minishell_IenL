/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_input.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: liz <liz@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 12:14:09 by liz           #+#    #+#                 */
/*   Updated: 2020/09/14 14:12:26 by liz           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char 	*ft_realloc(char **str, int count)
{
	*str = (char *)malloc(sizeof(char) * count + 1);
	return (*str);
}

// void get_input(char **input)
// {
// 	char buf;

// 	int i;
// 	i = 0;

// 	while (buf != '\n')
// 	{
// 		read(0, &buf, 1);
// 		printf("%c\n", buf);
// 		*input = ft_realloc(input, i);
// 		*input[i] = buf;
// 		printf(" input: %s\n", *input);
// 		i++;
// 	}
// 	// *input[i] = '\0';
// 	printf("%s\n", *input);
// }

char	*read_line(void)
{
	char *line;

	line = NULL;
	get_next_line(0, &line);
	return (line);
}