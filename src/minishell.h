#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <errno.h>
# include <dirent.h>
# include <term.h>
# include <string.h>

# define PROMT "Minihell!🔥"
# define APPEND_FILE 521
# define OUTPUT_FILE 1537

typedef struct s_dereference_utils
{
	char	*str;
	char	*start;
	char	*key;
	char	*answer;
	char	*new_src;
	char	**src;
	int		key_iter;
	int		state;
	int		break_flg;
}				t_dereference_utils;

//parser
typedef struct s_cmds
{
	char					*cmd_str;
	char					**args;
	char					**input_files;
	char					**output_files;
	char					**append_files;
	struct s_cmds			*next;
	int						file_type_flg;
}				t_cmds;

//to execute
typedef struct s_to_execute
{
	t_cmds		*cmds;
}				t_to_execute;

//lexer
typedef struct s_tok
{
	char			*data;
	int				type;
	struct s_tok	*next;
}					t_tok;

//parser
typedef struct s_pipelist
{
	t_tok				*tok_lst;
	struct s_pipelist	*next;
}						t_pipelist;

//lexer
typedef struct s_lexer
{
	t_tok	*tok_list;
	int		num_of_tokens;
	int		chtype;
	t_tok	*token;
	int		state;
	int		size;
	int		j;
}				t_lexer;

//parse utils
typedef struct s_parse_utils
{
	t_pipelist	*pipelist;
	t_tok		*cur_tok;
}				t_parse_utils;

typedef struct s_history
{
	char				*temp;
	char				*orig;
	struct s_history	*next;
	struct s_history	*prev;
}						t_history;

typedef struct s_todo
{
	t_dereference_utils	d_u;
	t_to_execute		*to_execute;
	t_lexer				*lex_buf;
	t_parse_utils		*parse_utils;
	char				**environments;
	struct termios		saved_attributes;
	int					exit_code;
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
void		build_to_execute_lst(t_todo *all);
void		destroy_to_execute_lst(t_todo *all);
void		parse_build(t_todo *all, t_cmds **cmds);
void		init_cmds_elem(t_cmds *cmds);
t_cmds		*get_new_cmds_elem(t_cmds *cmds);
void		get_cmd_str(t_cmds *cmds, t_tok *tok);
void		add_to_2d(char ***src, t_tok *tok);

//strip quotes and bslashes
void		strip_quotes_and_bslashes(char **src);

//dereference the value
void		dereference_the_value(t_todo *all);
char		*search_key(t_todo *all, char *key);
char		*put_nothing(char *src, char *start, char **stop);
char		*put_answer(char *src, char *start, char **stop, char *answer);
void		get_key(t_todo *all);

//build exec list
int			build_tokens(t_todo *all, char *line, int size,
				   t_lexer *lexer_list);

//tokenize
int			tokenize(char *line, int size, t_lexer *lexer_list);
void		if_state_in_general(t_lexer *lexer, char **line);
void		lexer_destroy(t_lexer *list);
void		tok_init(t_tok *tok, int data_size);
void		if_char_quote_do(t_lexer *lexer);
void		if_char_dquote_do(t_lexer *lexer);
void		if_char_escape_or_general_do(t_lexer *lexer, char **line);
void		if_char_whitespace_do(t_lexer *lexer, const char *line);
void		if_semi_great_less_pipe_char_do(t_lexer *lexer, const char *line);
int			get_num_of_type(char c);
void		tok_init(t_tok *tok, int data_size);
void		tok_destroy(t_tok *tok);
int			count_tokens(t_tok *token);
void		if_ch_is_quote_set_state_general(int *state, int *chtype);
void		if_ch_is_dquote_set_state_general(int *state, int *chtype);
void		get_chtype(char **line, int *chtype);
void		init_tokenizer(t_lexer *lexer, int size);
void		if_char_null_set_zero(t_lexer *lexer);
void		if_last_char_is_not_zero_do_line_pp(char **line);

//check syntax
int			check_syntax(t_todo *all, t_tok *token);
int			validate_quotation(char *str);

//parse pipes
void		parse_pipes(t_todo *all);
void		destroy_parse_pipes(t_todo *all);
void		init_pipe_list(t_todo *all, t_tok **src_lst,
				 t_tok **pipe_lst_tok, t_pipelist **pipelist);
void		init_tok(t_tok *lst);
t_pipelist	*get_next_pipe_list_elem(t_pipelist *pipe_lst);
t_tok		*get_next_tok_list_elem(t_tok *lst);

// builtins
int			ft_pwd(void);
int			ft_export(t_todo *all);
int			ft_cd(t_todo *all);
int			execute_cmd_pipe(t_todo *all);
int			ft_echo(t_todo *all);
int			ft_env(t_todo *all);
int			ft_exit(t_todo *all);
int			ft_unset(t_todo *all);

// utils
void		i_want_to_be_freed(char **arr);
int			execution(t_todo *all);
int			input_redirect(t_todo *all);
int			output_redirect(t_todo *all);
int			start_process(t_todo *all, char *bin);
int			do_builtin(char *path, t_todo *all);
int			is_builtin(char *path);
int			try_rel_abs_path(t_todo *all, int *flg);
char		*try_path(t_todo *all);
int			swapstr(char **str1, char **str2);
void		appendarg(char **str, char **appendix, int key_len);
int			ft_strcmp(char *str1, char *str2);
int			ft_putchar(int c);
int			validate_arg(char *newenv, char mode);
int			ft_checkforbiddensymbols_arg(char *str, int mode);
int			env_update(t_todo *all, char *key, char *change, char mode);
char		**env_search(char **env, char *key);
char		*env_get_value(t_todo *all, char *key);
void		env_set_value(t_todo *all, char *key, char *value);
void		set_shlvl(t_todo *all);
int			errorhandle(t_todo *all, char *program_name,
				  char *uniqe_error, char *code);
char		*try_open(t_todo *all);
int			set_redirections(t_todo *all);
t_history	*hist_new(char *content);
void		hist_add(t_history **lst, t_history *new);
void		hist_move_to_end(t_todo *all);
char		**clone_env(char **env, const char *new_env);
int			print_env(t_todo *all);
int			promt(t_todo *all);
int			termcap_stuff(t_todo *all);
int			check_input(char *buf, t_todo *all);
int			ctrlc(t_todo *all);
int			ctrld(t_todo *all);
char		*find_location(t_todo *all);

//libft
char		*ft_itoa(int n);
int			ft_atoi(const char *s);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
char		*ft_itoa(int n);
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putstr_fd(char *s, int fd);
char		**ft_split(char const *s, char c);
char		*ft_strchr(const char *s, int n);
char		*ft_strdup(const char *s);
char		*ft_strjoin(const char *s1, const char *s2);
size_t		ft_strlcat(char *dst, const char *src, size_t dsize);
size_t		ft_strlcpy(char *dst, const char *src, size_t dsize);
size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_substr(char const *s, unsigned int start, size_t len);

#endif
