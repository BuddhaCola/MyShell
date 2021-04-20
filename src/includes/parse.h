#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"
# include "parse.h"

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
#endif