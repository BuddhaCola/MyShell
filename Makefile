SRC = src/main.c \
src/utils/utils.c \
src/exec/env_functions.c \
src/exec/env_search.c \
src/exec/env_update.c \
src/exec/execution.c \
src/exec/execution_utils.c \
src/exec/execution_utils_2.c \
src/builtins/ft_cd.c \
src/builtins/ft_echo.c \
src/builtins/ft_env.c \
src/builtins/ft_exit.c \
src/builtins/ft_export.c \
src/builtins/ft_pwd.c \
src/builtins/ft_unset.c \
src/exec/pipe_execution.c \
src/exec/history.c \
src/exec/promt.c \
src/exec/promt_check_input_1.c \
src/exec/promt_check_input_2.c \
src/exec/redirections_and_appending.c \
src/exec/set_shlvl.c \
src/parse/build_tokens.c \
src/parse/tokenizer/tokenizer_utils2.c \
src/parse/tokenizer/tokenizer_utils.c \
src/parse/tokenizer/tokenize.c \
src/parse/tokenizer/lexer_destroy.c \
src/parse/tokenizer/if_state_in_general/if_state_in_general.c \
src/parse/tokenizer/if_state_in_general/if_state_in_general_utils.c \
src/parse/strip_quotes_and_bslashes/strip_quotes_and_bslashes.c \
src/parse/parse_pipes/parse_pipes.c \
src/parse/parse_pipes/init_pipe_list.c \
src/parse/parse_pipes/destroy_parse_pipes.c \
src/parse/dereferencing_dollar/dereference_the_value.c \
src/parse/dereferencing_dollar/deref_utils.c \
src/parse/check_syntax/validate_quotation.c \
src/parse/check_syntax/check_syntax.c \
src/parse/build_to_execute_lst/detroy_to_excute_list.c \
src/parse/build_to_execute_lst/build_to_execute_lst_utils.c \
src/parse/build_to_execute_lst/build_to_execute_lst.c \
src/parse/build_to_execute_lst/add_to_2d.c \
src/utils/ft_atoi.c \
src/utils/ft_bzero.c \
src/utils/ft_calloc.c \
src/utils/ft_isalnum.c \
src/utils/ft_isalpha.c \
src/utils/ft_isdigit.c \
src/utils/ft_isprint.c \
src/utils/ft_itoa.c \
src/utils/ft_putchar_fd.c \
src/utils/ft_putendl_fd.c \
src/utils/ft_putstr_fd.c \
src/utils/ft_split.c \
src/utils/ft_strchr.c \
src/utils/ft_strdup.c \
src/utils/ft_strjoin.c \
src/utils/ft_strlcat.c \
src/utils/ft_strlen.c \
src/utils/ft_strncmp.c \
src/utils/ft_strlcpy.c \
src/utils/ft_substr.c \
src/utils/ft_strcmp.c

NAME	=	minishell

OBJ		=	$(SRC:.c=.o)

FLAGS	=	-Wall -Werror -Wextra

all:		$(NAME)

$(NAME): $(OBJ) src/minishell.h
	$(CC) -ltermcap $(OBJ) -o $(NAME)

.c.o:
	gcc $(FLAGS) -c $< -o $(<:.c=.o)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re