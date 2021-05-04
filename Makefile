# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wtaylor <wtaylor@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/11 15:54:29 by wtaylor           #+#    #+#              #
#    Updated: 2021/04/20 21:36:09 by wtaylor          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = src/main.c \
src/utils/get_next_line/get_next_line.c src/utils/get_next_line/get_next_line_utils.c src/utils/utils.c\
src/exec/env_functions.c src/exec/exec_bin.c src/exec/ft_echo.c src/exec/ft_env.c src/exec/ft_exit.c src/exec/ft_export.c src/exec/ft_pipe.c src/exec/ft_pwd.c src/exec/path_parse.c src/exec/redirection.c src/exec/ft_unset.c src/exec/update_env.c\
src/parse/lexer/lexer.c src/parse/parser/parser.c src/parse/lexer/strip_quotes/strip_quotes.c src/parse/dereferencing_dollar/dereference_the_value.c

NAME	=	minishell

LIBFT	=	src/utils/libft

OBJ		=	$(SRC:.c=.o)

FLAGS	=	#-Wall -Werror -Wextra

all:		$(NAME)

$(NAME): $(OBJ) src/minishell.h
	make bonus -C $(LIBFT)
	$(CC) -g -ltermcap $(OBJ) $(LIBFT)/libft.a -o $(NAME)

address_sanitize:	$(OBJ) src/minishell.h #убрать! 🚧
	make bonus -C $(LIBFT)
	$(CC) -ggdb -fsanitize=address -fno-omit-frame-pointer -g -ltermcap  $(OBJ) $(LIBFT)/libft.a -o $(NAME)

.c.o:
	gcc $(FLAGS) -g -c $< -o $(<:.c=.o)

clean:
	rm -f $(OBJ)
	make clean -C $(LIBFT)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT)

re: fclean all

.PHONY: clean fclean all re