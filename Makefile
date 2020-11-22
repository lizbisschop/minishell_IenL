# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lbisscho <lbisscho@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/11/22 16:52:42 by lbisscho      #+#    #+#                  #
#    Updated: 2020/11/22 20:32:37 by iboeters      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = libft.a

SRCS = ./gnl/get_next_line.c \
	./gnl/get_next_line_utils.c \
	mini_main.c \
	show_command_prompt.c \
	which_command.c \
	pwd.c \
	quotes.c \
	envp.c \
	tokens.c \
	check_for_errors.c \
	mini_utils.c \
	echo.c \
	cd.c \
	free_stuff.c \
	export.c \
	export2.c \
	read_line.c \
	exec_cmd.c \
	sort_env.c \
	pipes.c \
	unset.c \
	redirections.c \
	tokenizer.c \
	get_path.c \
	exec_child.c \
	valid_input_redir.c \
	multi_lines.c \
	exec_exit.c \
	check_for_dollar.c \
	ft_split_commands.c \
	insertion_sort.c \
	save_commands.c \
	check_pip_redir.c \
	mini_utils_2.c \
	signal_handlers.c \
	get_env_var.c \
	expand_tokens.c \
	expand_tokens_pipes.c \
	remove_empty_tokens.c \
	free_stuff_2.c \
	var_sub.c

FLAGS = -Wall -Werror -Wextra

OBJ = $(SRCS:.c=.o)

INCL = -I minishell.h -I ./libft/libft.h -I ./gnl/get_next_line.h

ifdef DEBUG
FLAGS += -fsanitize=address -fno-omit-frame-pointer -g
endif

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	gcc $(FLAGS) $^ $(INCL) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C ./libft
	cp ./libft/libft.a .

clean:
	@make clean -C ./libft
	rm -rf $(OBJ)

fclean: clean
	@make fclean -C ./libft
	rm -rf $(LIBFT)
	rm -rf $(NAME)

re: fclean all
