#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
// #include "parse.h"
// #include "structs.h"
#include "utils/get_next_line/get_next_line.h"
#include "utils/libft/libft.h"

#define PROBE printf("here!\n"); //убрать на продакшне!
#define PROMT "minishell 👉"

typedef struct s_tok
{
	char			*data;
	int				type;
	struct s_tok	*next;
}					t_tok;

typedef struct s_lexer
{
	t_tok	*tok_list;
	int		num_of_tokens;
}				t_lexer;

typedef struct	s_env
{
	char *name;
	char *value;
}				t_env;

typedef struct  s_simple_command
{
	int         number_of_available_arguments;
	int         number_of_arguments;
	char        **arguments;
}               t_simple_command;

typedef struct          s_command
{
	int                 number_of_available_simle_commands;
	int                 number_of_simple_commands;
	t_simple_command    **simple_commands;
	char                *out_file;
	char                *input_file;
	char                *err_file;
	int                 background;
}                       t_command;

typedef	struct s_exec
{
	char				**env;
	int 				err;
}						t_exec;

typedef	struct			s_todo
{
    t_simple_command    simple_command;
    t_command           command;
	t_exec				exec;
	t_lexer				*lex_buf;
	t_env 				*environments;
	int 				env_count;
}						t_todo;

enum e_token_type
{
	CHAR_WHITESPACE = ' ',
	CHAR_SEMICOLON = ';',
	CHAR_QUOTE = '\'',
	CHAR_DQUOTE = '\"',
	CHAR_PIPE = '|',
	CHAR_AMPERSAND = '&',
	CHAR_ESCAPESEQ = '\\',
	CHAR_TAB = '\t',
	CHAR_NEWLINE = '\n',
	CHAR_GREATER = '>',
	CHAR_LESSER = '<',
	CHAR_NULL = 0,
	CHAR_GENERAL = -1,
	TOKEN = -1,
};

enum e_states
{
	STATE_IN_DQUOTE,
	STATE_IN_QUOTE,
	STATE_IN_ESCAPEDSEQ,
	STATE_GENERAL,
};

int		get_num_of_type(char c);
void	tok_init(t_tok *tok, int data_size);
void	tok_destroy(t_tok *tok);
int		lexer_build(char *line, int size, t_lexer *lexer_list);
void	lexer_destroi(t_lexer *list);
void	strip_quotes(char *src, char *dst);

int collect_env(t_todo *all, char **env);
void 	handle_signals();

// builtins
void	ft_pwd(void);
int		ft_export(t_todo *all, char **args);
int		ft_pipe(char *program1, char **arg1, char *program2, char **arg2);
int		ft_echo(int argc, char **argv);
int 	ft_env(t_todo *all);

// utils
int		exec_bin(char *path, t_todo *all);
int		redirection(char *filepath, char *program, char **args, int append);
int		count_environments(t_todo *all);

#endif
