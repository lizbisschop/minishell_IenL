# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: liz <liz@student.codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2020/09/14 11:50:17 by liz           #+#    #+#                  #
#    Updated: 2020/09/15 10:58:54 by liz           ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = libft.a

GNL = ./gnl/get_next_line.c ./gnl/get_next_line_utils.c

SRCS = mini_main.c show_command_prompt.c get_input.c which_command.c echo.c \
	pwd.c

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