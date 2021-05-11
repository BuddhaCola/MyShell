#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
#include <term.h>
#include <string.h>


#include "utils/get_next_line/get_next_line.h"
#include "utils/libft/libft.h"

#define PROBE printf("🤘Got here🤘\n"); //убрать на продакшне!
#define PROMT "Minihell!🔥"

#define NONE 0
#define APPEND_FILE 521
#define OUTPUT_FILE 1537

//parser
typedef struct s_cmds
{
	char					*cmd_str;
	char					**args;
	char					**input_files;
	char					**output_files;
	char                    **append_files;
	int 					file_type_flg;
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
	int 	chtype;
	t_tok	*token;
	int		state;
	int     size;
	int		j;
}				t_lexer;

//parse utils
typedef struct  s_parse_utils
{
	t_pipelist  *pipelist;
	t_tok *cur_tok;
}               t_parse_utils;

typedef struct			s_history
{
	char 				*temp;
	char				*orig;
	struct s_history	*next;
	struct s_history	*prev;
}						t_history;

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
	struct termios		saved_attributes;
	int 				exit_code;
	t_history			*hist_curr;
	t_cmds				*cur_cmds;
	int					orig_stdin;
	int					orig_stdout;
}						t_todo;

enum e_token_type
{
	CHAR_WHITESPACE = ' ',
	CHAR_SEMICOLON = ';',
	CHAR_QUOTE = '\'',
	CHAR_DQUOTE = '\"',
	CHAR_PIPE = '|',
	CHAR_ESCAPESEQ = '\\',
	CHAR_TAB = '\t',
	CHAR_NEWLINE = '\n',
	CHAR_GREATER = '>',
	CHAR_LESSER = '<',
	CHAR_DGREATER = -2,
	CHAR_NULL = 0,
	CHAR_GENERAL = -1,
	TOKEN = -1,
};

enum e_states
{
	STATE_IN_DQUOTE,
	STATE_IN_QUOTE,
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
int build_tokens(t_todo *all, char *line, int size
		,t_lexer *lexer_list);

//tokenize
int         tokenize(char *line, int size, t_lexer *lexer_list);
void 		if_state_in_general(t_lexer *lexer, char *line);
void		lexer_destroy(t_lexer *list);
void tok_init(t_tok *tok, int data_size);
void if_char_quote_do(t_lexer *lexer);
void if_char_dquote_do(t_lexer *lexer);
void if_char_escape_or_general_do(t_lexer *lexer, const char *line);
void if_char_whitespace_do(t_lexer *lexer, const char *line);
void if_semi_great_less_pipe_char_do(t_lexer *lexer, const char *line);
int  get_num_of_type(char c);
void tok_init(t_tok *tok, int data_size);
void		tok_destroy(t_tok *tok);
int count_tokens(t_tok *token);
void if_ch_is_quote_set_state_general(int *state, int *chtype);
void if_ch_is_dquote_set_state_general(int *state, int *chtype);
void get_chtype(char **line, int *chtype);
void init_tokenizer(t_lexer *lexer, int size);
void if_char_null_set_zero(t_lexer *lexer);
void if_last_char_is_not_zero_do_line_pp(char **line);




//check syntax
int check_syntax(t_todo *all, t_tok *token);

//parse pipes
void    parse_pipes(t_todo *all);
void    destroy_parse_pipes(t_todo *all);

char	**clone_env(char **env, const char *new_env);
void	handle_signals();
int		print_env(t_todo *all);

// builtins
int		ft_pwd(void);
int		ft_export(t_todo *all);
int		ft_cd(t_todo *all);
int		ft_pipe(t_todo *all);
//int		ft_pipe(char *program1, char **arg1, char *program2, char **arg2);
int 	ft_echo(t_todo *all);
int		ft_env(t_todo *all);
int		ft_exit(t_todo *all);
int		ft_unset(t_todo *all);

// utils
void	i_want_to_be_freed(char **arr);
int		execution(t_todo *all);
int		input_redirect(t_todo *all);
int		output_redirect(t_todo *all);
int		start_process(t_todo *all, char *bin);
int		do_builtin(char *path, t_todo *all);
int		is_builtin(char *path);
int		try_rel_abs_path(t_todo *all);
char	*try_path(t_todo *all);
int		redirection(char *filepath, char *program, char **args, int append);
int		count_environments(t_todo *all);
int		swapstr(char **str1, char **str2);
void	appendarg(char **str, const char **appendix, int key_len);
//char	*get_env_value(t_todo *all, char *name);
char	*path_parse(t_todo *all, char *arg);

int		ft_strcmp(char *str1, char *str2);
int		ft_putchar(int c);
int		validate_arg(char *newenv, char mode);
int		ft_checkforbiddensymbols_arg(char *str, int mode);
int		env_update(t_todo *all, char *key, char *change, char mode);
char	**env_search(char **env, char *key);
char	*env_get_value(t_todo *all, char *key);
void	env_set_value(t_todo *all, char *key, char *value);
void	set_shlvl(t_todo *all);
int		errorhandle(t_todo *all, char *program_name, char *uniqe_error, char *code);

t_history 	*hist_new(char *content);
void		hist_add(t_history **lst, t_history *new);
void		hist_move_to_end(t_todo *all);

//void	hist_print(t_todo *all);

#endif
