#ifndef PARSE_H
# define PARSE_H

# include "../minishell.h"

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

typedef struct s_tok
{
	char	*data;
	int		type;
	t_tok	*next;
}				t_tok;

typedef struct s_lexer
{
	t_tok	*tok_list;
	int		num_of_tokens;
}				t_lexer;

int		get_num_of_type(char c);
void	tok_init(t_tok *tok, int data_size);
void	tok_destroy(t_tok *tok);
int		lexer_build(t_todo *all);
void	lexer_destroi(t_lexer *list);
int		strip_quotes(char *src, char *dest);

#endif