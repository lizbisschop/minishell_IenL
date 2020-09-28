NAME = minishell

LIBFT = libft.a

GNL = ./gnl/get_next_line.c ./gnl/get_next_line_utils.c

SRCS = mini_main.c \
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
	echo.c 
	# cd.c \

OBJ = $(SRCS:.c=.o)

INCL = minishell.h ./libft/libft.h ./gnl/get_next_line.h

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	gcc -Wall -Werror -Wextra $(SRCS) $(GNL) $(LIBFT) $(INCL) -o $(NAME)

$(LIBFT):
	# make -C ./libft
	# cp ./libft/libft.a .

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf minishell

re: fclean all