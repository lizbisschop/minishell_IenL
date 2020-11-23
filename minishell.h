/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: iboeters <iboeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/09 18:19:53 by iboeters      #+#    #+#                 */
/*   Updated: 2020/11/23 13:43:02 by iboeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <errno.h>
# include <limits.h>
# include <dirent.h>
# include "./libft/libft.h"
# include "./gnl/get_next_line.h"
# define EXT_ALPHABET_SIZE 63
# define PID_MAX 709

typedef	struct	s_command{
	int			tok_amount;
	char		**tokens;
	int			invalid_redir;
	int			error_redir;
}				t_command;

typedef	struct	s_mini{
	int			main_in;
	int			main_out;
	int			fd_in;
	int			fd_out;
	int			found_in;
	int			found_out;
	int			fd;
	int			fd2;
	int			cmds;
	int			pipe_cmds;
	int			n_quotes;
	int			end;
	char		*input;
	char		**sp_input;
	char		**env;
	int			*arr;
	char		**export_fill;
	int			piped;
	int			in_redir;
	int			out_redir;
	int			exit_int;
	char		q;
	int			check_export;
	char		*export_str;
	char		*nbr;
	char		*pwd;
	int			i_tok;
	int			array_len;
	int			use_string;
	int			cmd;
	int			env_i;
	t_command	*c;
	t_command	*pipes_c;
}				t_mini;

void			show_command_prompt(void);
char			*get_input(void);
void			skip_whitespaces(char *str, t_mini *mini);
void			echo(char **tokens, int tok_amount, t_mini *mini);
void			which_command(t_mini *mini);
void			pwd(t_mini *mini);
int				cd(char **tokens, int tok_amount, t_mini *mini);
void			set_envp(t_mini *mini);
int				multi_lines(char *str);
char			*unquote(char **s, t_mini *mini);
int				env_command(int check, t_mini *mini);
char			**ft_split_minishell(char const *s, char c, t_mini *mini);
int				ft_split_commands(char *s, t_mini *mini);
int				string_count(t_mini *mini, char *s);
int				check_for_errors(char *s, t_mini *mini);
void			tokens(t_mini *mini);
void			skip_wspaces(char *s, int *i);
int				is_whitespace(char c);
int				is_delimiter(char c);
void			free_stuff(t_mini *mini);
char			**copy_env(void);
void			ft_export(char **tokens, int tok_amount, t_mini *mini);
void			set_env(char *s, t_mini *mini);
int				*sort_env(char **env);
char			*read_line(t_mini *mini);
void			exec_cmd(char **tokens, char *s, t_mini *mini);
char			*ft_strjoin_read(char *s1, char *s2);
char			*ft_strdup_free(char **s1);
void			check_for_dollar(char **token, t_mini *mini);
int				pipes(t_mini *mini, int cmd);
void			unset(char **tokens, t_mini *mini);
int				multi_line_pipe(t_mini *mini);
void			find_command(char **tokens, int tok_amount, t_mini *mini);
int				check_redir(char ***tokens, int *tok_amount, t_mini *mini);
int				valid_input_redir(t_command *command, t_mini *mini);
int				tokenizer(char **tokens, int tok_amount, t_mini *mini);
char			*get_pwd(void);
void			free_env_export(t_mini *mini);
void			free_pipes_c(t_mini *mini);
char			*get_home(t_mini *mini);
char			*get_path(char *cmd, t_mini *mini);
void			err(char *function, char *input, int fd, t_mini *mini);
int				exec_child(char **tokens, char *s, t_mini *mini);
void			error_multi_line_pipe(int i, int cmd, t_command command,
t_mini *mini);
int				multi_line_pipe(t_mini *mini);
int				multi_lines(char *str);
void			exec_exit(t_mini *mini, int tok_amount, char **tokens);
void			free_env(t_mini *mini);
char			**add_to_env(char *s, t_mini *mini);
void			if_quote(int *k, int *j, t_mini *mini);
void			find_right_env(t_mini *mini, int *i, int *j, int *k);
void			skip_quoted(char *s, int *i);
void			print_export(t_mini *mini);
void			check_quotes(char *s, t_mini *mini);
void			insertion_sort(int end, int start, int *arr, char **env);
int				save_commands(t_mini *mini, char *s);
int				check_pip_redir(int *i, char *s, t_mini *mini);
int				check_delimiter(char *s, t_mini *mini, int *i);
int				check_output_redir(char *s, t_mini *mini, int *i);
int				check_semicolon(char *s, t_mini *mini, int *i);
int				check_redir_end(int *i, char *str, t_mini *mini);
void			quotes(char **tokens, t_mini *mini);
void			var_sub(char **tokens, t_mini *mini, int cmd);
void			signal_child(void);
void			handle_sigint(int signal);
void			handle_sigquit(int signal);
void			malloc_error(void);
void			get_env_var(int *i, char **token, t_mini *mini, char **str);
int				dollar_quote(int *i, char **token, t_mini *mini, char **str);
void			dollar_questionmark(t_mini *mini, char **str, int *i);
void			expand_tokens(t_mini *mini, char **str, int i, char *env);
void			expand_tokens_pipes(t_mini *mini, char **str, int i, char *env);
void			set_open_q(char token, t_mini *mini);
void			remove_empty_token(t_mini *mini, int remove);
void			remove_empty_token_pipes(t_mini *mini, int remove);
void			free_old_tokens(char ***old_tokens);
void			free_tokens(t_mini *mini, char **array);
void			free_tokens_pipes(t_mini *mini, char **array);
void			var_sub(char **tokens, t_mini *mini, int cmd);
void			close_and_free(t_mini *mini, char **s);
int				check_semicolon(char *s, t_mini *mini, int *i);
void			switch_quotes(t_mini *mini, char *q, char *anti_q);

#endif
