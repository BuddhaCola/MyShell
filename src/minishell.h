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
typedef struct s_cmd
{
	char					*cmd_str;
	char					**args;
	int						flg_pipe_left;
	int						flg_pipe_right;
	int						flg_redir_in;
	int						flg_redir_out;
	char					**input;
	char					**output;
	struct s_cmd		    *next;
}				t_cmd;

typedef struct s_custom_list
{
	t_cmd		            *cmd;
    struct s_custom_list    *next;
}				t_custom_list;

//lexer
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
    t_custom_list 		*simple_command_list;
    t_tok               *cur_tok_list;
    t_custom_list 		*cur_simple_command_list;
	t_exec				exec;
	t_lexer				*lex_buf;
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

//parse
void parse(t_todo *all);
static void parse_build(t_todo *all);
static void init_cmd(t_todo *all);
static int  check_non_general(t_todo *all);
void destroy_parser(t_todo *all);
void reset_parser(t_todo *all);


//lexer
int		get_num_of_type(char c);
void	tok_init(t_tok *tok, int data_size);
void	tok_destroy(t_tok *tok);
int		lexer_build(char *line, int size, t_lexer *lexer_list);
void	lexer_destroi(t_lexer *list);
void	strip_quotes(char *src, char *dst);

int		collect_env(t_todo *all, char **env);
void 	handle_signals();
int		print_env(t_todo *all);

// builtins
void	ft_pwd(void);
int		ft_export(t_todo *all, char *args);
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

#endif
