# ifndef STRUCTS_H
#define STRUCTS_H

#include "../includes/minishell.h"

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
	t_env 				*environments;
}						t_exec;

typedef	struct			s_todo
{
    t_simple_command    simple_command;
    t_command           command;
	t_exec				exec;
	t_lexer				*lex_buf;
}						t_todo;

#endif