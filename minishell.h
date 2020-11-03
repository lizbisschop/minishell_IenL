#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <signal.h>
#include <errno.h>
#include <limits.h>
#include <dirent.h>
#include "./libft/libft.h"
#include "./gnl/get_next_line.h"

//REMOVE!!!
#include <stdio.h>

typedef	struct	s_command{
	int			tok_amount;
	char		**tokens;
	int			invalid_input;
}				t_command;

typedef	struct	s_mini{
	int			main_in;
	int			main_out;
	int			main_err;
	int			cmds;
	int			pipe_cmds;
	int			end;
	char		*input;
	char		**sp_input;
	char		**env;
	char		**export_env;
	int			piped;
	int			in_redir;
	int			out_redir;
	int			exit_int;
	t_command	*c;
	t_command	*pipes_c;
}				t_mini;

// extern char **mini->env;

void	show_command_prompt(void);
char	*get_input(void);
void	skip_whitespaces(char *str, t_mini *mini);
void	echo(char **tokens, int tok_amount, t_mini *mini);
void	which_command(t_mini *mini);
void	pwd(t_mini *mini);
int		quotes(t_mini *mini, char c, char *line);
int		cd(char **tokens, int tok_amount, t_mini *mini);
void	set_envp(t_mini *mini);
int		multi_lines(char *str);
char	*unquote(char **s, t_mini *mini);
int		env_command(int check, t_mini *mini);
char	**ft_split_minishell(char const *s, char c, t_mini *mini);
int		ft_split_commands(char *s, t_mini *mini);
int		string_count(t_mini *mini, char *s);
int		check_for_errors(char *s, t_mini *mini);
int		tokens(t_mini *mini);
void	skip_wspaces(char *s, int *i);
int		is_whitespace(char c);
int		is_delimiter(char c);
void	free_stuff(t_mini *mini);
char	**copy_env(void);
void	ft_export(char **tokens, int tok_amount, t_mini *mini);
void	set_env(char *s, t_mini *mini);
char	**sort_env(char **str, t_mini *mini);
char	*read_line(void);
int		exec_cmd(char **tokens, char *s, t_mini *mini);
char	*ft_strjoin_read(char *s1, char *s2);
char	*ft_strdup_free(char **s1);
void	check_for_dollar(char **token, t_mini *mini);
int		pipes(t_mini *mini, int cmd);
void	unset(char **tokens, t_mini *mini);
int		multi_line_pipe(t_mini *mini);
int		find_command(char **tokens, int tok_amount, t_mini *mini);
void	check_redir(int *fd_out, int *fd_in, char ***tokens, int *tok_amount, t_mini *mini);
int		valid_input_redir(t_command *command, t_mini *mini);
int		tokenizer(char **tokens, int tok_amount, t_mini *mini);
char	*get_pwd(void);
void	free_env_export(t_mini *mini);
char	*get_home(t_mini *mini);
char	*get_path(char *cmd);
void	err(char *function, char *input, int fd, t_mini *mini);

#endif
