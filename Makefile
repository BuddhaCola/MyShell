# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wtaylor <wtaylor@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/11 15:54:29 by wtaylor           #+#    #+#              #
#    Updated: 2021/04/11 17:33:50 by wtaylor          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = src/main.c src/utils.c
 
# BONUS = ft_lstadd_back.c ft_lstdelone.c ft_lstmap.c ft_lstadd_front.c\
# ft_lstiter.c ft_lstnew.c ft_lstclear.c ft_lstlast.c ft_lstsize.c\

NAME	=	minishell

OBJ		=	$(SRC:.c=.o)

OBONUS	=	$(BONUS:.c=.o)

FLAGS	=	#-Wall -Werror -Wextra

all:		$(NAME)

$(NAME): $(OBJ) src/minishell.h
	$(CC) $(OBJ) -o $(NAME)

# bonus:	$(OBJ)	$(OBONUS)
# 		ar rc $(NAME) $(OBJ) $(OBONUS)

.c.o:
	gcc $(FLAGS) -c $< -o $(<:.c=.o)

clean:
	rm -f $(OBJ) $(OBONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re #bonus