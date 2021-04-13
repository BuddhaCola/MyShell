# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wtaylor <wtaylor@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/11 15:54:29 by wtaylor           #+#    #+#              #
#    Updated: 2021/04/12 14:24:48 by wtaylor          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = src/main.c \
src/utils/get_next_line/get_next_line.c src/utils/get_next_line/get_next_line_utils.c \
src/exec/ft_env.c src/exec/ft_pwd.c src/exec/ft_echo.c src/exec/exec_bin.c\

NAME	=	minishell

LIBFT	=	src/utils/libft/libft.a

OBJ		=	$(SRC:.c=.o)

FLAGS	=	#-Wall -Werror -Wextra

all:		$(NAME)

$(NAME): $(OBJ) src/minishell.h
	$(CC) $(OBJ) $(LIBFT) -o $(NAME)

.c.o:
	gcc $(FLAGS) -g -c $< -o $(<:.c=.o)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re