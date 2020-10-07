#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <signal.h>
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
	int			slash;
	char		*new_input;
	int			end;
	char		**env;
	char		**export_env;
	char		*set;
	char		*alias;
	char		*def;
	t_command	*c;
}				t_mini;

// extern char **mini->env;

void	show_command_prompt(void);
char	*get_input(void);
void	skip_whitespaces(char *str, t_mini *mini);
void	echo(t_command command, t_mini *mini);
void	which_command(t_mini *mini);
void	pwd(void);
int		quotes(t_mini *mini, char c, char *line);
int		cd(t_command command, t_mini *mini);
void	set_envp(t_mini *mini);
int		multi_lines(char *str);
char	*unquote(char **s);
int	env_command(int check, t_mini *mini);
char	**ft_split_minishell(char const *s, char c, t_mini *mini);
int		ft_split_commands(char *s, t_mini *mini);
int		string_count(t_mini *mini, char *s);
int		check_for_errors(char *s);
int		tokens(t_mini *mini);
void	skip_wspaces(char *s, int *i);
int		is_whitespace(char c);
int		is_delimiter(char c);
void	free_stuff(t_mini *mini);
char	**copy_env(void);
void	ft_export(t_command command, t_mini *mini);
void	set_env(char *s, t_mini *mini);
char	**sort_env(char **str);
char	*read_line(void);

#endif