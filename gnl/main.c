/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbisscho <lbisscho@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/20 13:53:43 by lbisscho       #+#    #+#                */
/*   Updated: 2020/04/02 17:11:04 by liz           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */




#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int count;
	int fd;
	char *line;

	count = 1; 
	fd = open("get_next_line.c", O_RDONLY);
	while (count > 0)
	{
		count = get_next_line(fd, &line);
		printf("%d | %s\n", count, line);
		free(line);
	}
	// while (fd)
	// {
		
	// }
	// count = get_next_line(fd, &line);
	// printf("%d | \n", count);
	return (0);
}