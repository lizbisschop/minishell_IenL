NAME = minishell

LIBFT = libft.a

GNL = ./gnl/get_next_line.c ./gnl/get_next_line_utils.c

SRCS = ./gnl/get_next_line.c \
	./gnl/get_next_line_utils.c \
	mini_main.c \
	show_command_prompt.c \
	get_input.c \
	which_command.c \
	pwd.c \
	quotes.c \
	envp.c \
	ft_split_commands.c \
	tokens.c \
	check_for_errors.c \
	mini_utils.c \
	echo.c \
	cd.c \
	free_stuff.c \
	export.c \
	read_line.c \
	exec_cmd.c \
	sort_env.c \
	pipes.c \
	unset.c \
	redirections.c \
	tokenizer.c \
	

FLAGS = -Wall -Werror -Wextra

OBJ = $(SRCS:.c=.o)

INCL = -I minishell.h -I ./libft/libft.h -I ./gnl/get_next_line.h

ifdef DEBUG
FLAGS += -fsanitize=address -fno-omit-frame-pointer -g
endif

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	gcc $(FLAGS) $^ $(INCL) $(LIBFT) -o $(NAME) -g

# %.o: %.c
# 	gcc -Wall -Werror -Wextra -c $< -o $@

$(LIBFT):
	# make -C ./libft
	# cp ./libft/libft.a .

clean:
	@make clean -C ./libft
	rm -rf $(OBJ)

fclean: clean
	@make fclean -C ./libft
	# rm -rf $(LIBFT)
	rm -rf $(NAME)

re: fclean all
