#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
#include <term.h>


#include "utils/get_next_line/get_next_line.h"
#include "utils/libft/libft.h"

#define PROBE printf("🤘Got here🤘\n"); //убрать на продакшне!
#define PROMT "Minihell!🔥"

//parser
typedef struct s_cmds
{
	char					*cmd_str;
	char					**args;
	char					**input_files;
	char					**output_files;
	char                    **append_files;
	struct s_cmds		    *next;
}				t_cmds;

//to execute
typedef struct s_to_execute
{
	t_cmds		            *cmds;
}				t_to_execute;

//lexer
typedef struct s_tok
{
	char			*data;
	int				type;
	struct s_tok	*next;
}					t_tok;

//parser
typedef struct  s_pipelist
{
    t_tok               *tok_lst;
    struct s_pipelist   *next;
}               t_pipelist;

//lexer
typedef struct s_lexer
{
	t_tok	*tok_list;
	int		num_of_tokens;
}				t_lexer;

//parse utils
typedef struct  s_parse_utils
{
    t_pipelist  *pipelist;
    t_tok *cur_tok;
}               t_parse_utils;

//typedef struct	s_env
//{
//	char *name;
//	char *value;
//}				t_env;

typedef	struct s_exec
{
	char				**env;
	int 				err;
}						t_exec;

typedef	struct			s_todo
{
    t_to_execute		*to_execute;
	t_exec				exec;
	t_lexer				*lex_buf;
    t_parse_utils       *parse_utils;
	char 				**environments;
	int 				env_count;
	struct termios		saved_attributes;
	char 				terminfo_buffer[2048];
	int 				exit_code;
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
	CHAR_DOLLAR = '$',
	CHAR_DGREATER = -2,
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

//build to execute lst
void build_to_execute_lst(t_todo *all);
void destroy_to_execute_lst(t_todo *all);

//strip quotes and bslashes
void strip_quotes_and_bslashes(char **src);

//dereference the value
void dereference_the_value(t_todo *all);

//build exec list
int build_execute_lst(t_todo *all, char *line, int size
        ,t_lexer *lexer_list);

//tokenize
int         tokenize(char *line, int size, t_lexer *lexer_list);
void		lexer_destroy(t_lexer *list);

//check syntax
int check_syntax(t_tok *token);

//parse pipes
void    parse_pipes(t_todo *all);
void    destroy_parse_pipes(t_todo *all);

char	**clone_env(char **env, const char *new_env);
void	handle_signals();
int		print_env(t_todo *all);

// builtins
void	ft_pwd(void);
int		ft_export(t_todo *all);
int		ft_pipe(char *program1, char **arg1, char *program2, char **arg2);
int		ft_echo(int argc, char **argv);
int		ft_env(t_todo *all);
int		ft_exit(char **args, t_todo *all);

// utils
void	i_want_to_be_freed(char **arr);
int		exec_bin(char *path, t_todo *all);
int		redirection(char *filepath, char *program, char **args, int append);
int		count_environments(t_todo *all);
//char	*get_env_value(t_todo *all, char *name);
char	*path_parse(t_todo *all, char *arg);

int ft_strcmp(char *str1, char *str2);
int ft_putchar(int c);

char	**env_search(char **env, char *key);
char	*env_get_value(t_todo *all, char *key);


#endif
