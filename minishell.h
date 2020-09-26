#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include "./libft/libft.h"
#include "./gnl/get_next_line.h"

//REMOVE!!!
#include <stdio.h>

typedef	struct	s_command{
	int			tok_amount;
	char		**tokens;
}				t_command;

typedef	struct	s_mini{
	int			i;
	int			cmds;
	int			end_string;
	char		*input;
	char		**sp_input;
	char		**envp;
	int			slash;
	char		*new_input;
	int			end;
	t_command	*c;
}				t_mini;

void	show_command_prompt(void);
char	*get_input(void);
void	skip_whitespaces(char *str, t_mini *mini);
void	echo(char *str, t_mini *mini);
void	which_command(t_mini *mini, char **envp);
void	pwd(void);
int		quotes(t_mini *mini, char c, char *line);
int		cd(char *str, t_mini *mini, char **envp);
void	set_envp(t_mini *mini, char **envp);
int		multi_lines(char *str);
char	*unquote(char **s);
void	env_command(char **envp);
char	**ft_split_minishell(char const *s, char c, t_mini *mini);
void	ft_split_commands(char *s, t_mini *mini);
int		string_count(t_mini *mini, char *s);
int		check_for_errors(char *s);
int		tokens(t_mini *mini);
void	skip_wspaces(char *s, int *i);
int		is_whitespace(char c);
int		is_delimiter(char c);

#endif