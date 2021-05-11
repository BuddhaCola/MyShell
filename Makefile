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
src/exec/env_functions.c src/exec/execution.c src/exec/execution_utils.c src/exec/ft_echo.c src/exec/ft_env.c src/exec/ft_exit.c src/exec/ft_export.c src/exec/ft_pipe.c src/exec/ft_pwd.c src/exec/path_parse.c src/exec/redirection.c src/exec/ft_unset.c src/exec/env_update.c src/exec/set_shlvl.c src/exec/env_search.c src/exec/ft_cd.c src/exec/error_handle.c src/exec/history.c\
src/parse/dereferencing_dollar/dereference_the_value.c src/parse/parse_pipes/parse_pipes.c \
src/parse/tokenizer/tokenize.c src/parse/build_to_execute_lst/build_to_execute_lst.c\
src/parse/build_execute_lst.c src/parse/check_syntax/check_syntax.c \
src/parse/strip_quotes_and_bslashes/strip_quotes_and_bslashes.c

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