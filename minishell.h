/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: liz <liz@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 11:37:41 by liz           #+#    #+#                 */
/*   Updated: 2020/09/14 14:44:40 by liz           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include "./libft/libft.h"
#include "./gnl/get_next_line.h"

//REMOVE!!!
#include <stdio.h>

void show_command_prompt(void);
void get_input(char **input);
char 	*ft_realloc(char **str, int count);
char *read_line(void);
void skipping_spaces(char *str, int *count);
void	echo(char *str);
void 	which_command(char *input);




#endif