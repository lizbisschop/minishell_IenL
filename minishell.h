/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: liz <liz@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 11:37:41 by liz           #+#    #+#                 */
/*   Updated: 2020/09/17 16:18:18 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include "./libft/libft.h"
#include "./gnl/get_next_line.h"

//REMOVE!!!
#include <stdio.h>

typedef struct 	s_mini {
	int		i;
	int		cmds;
	int		end_command;
	char	*input;
	char	**sp_input;
	char	*command;
}	t_mini;

void	show_command_prompt(void);
void	get_input(char **input);
char	*read_line(void);
void	skip_whitespaces(char *str, t_mini *mini);
void	echo(char *str, t_mini *mini);
void 	which_command(t_mini *mini);
void	pwd(void);
char	**split_input(char *str);
int		quotes(t_mini *mini, char c, char *line);
void 	cd(char *str, t_mini *mini);

#endif