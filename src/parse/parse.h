#ifndef PARSE_H
# define PARSE_H

# include "../minishell.h"

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
;
#endif