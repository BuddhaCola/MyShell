#include "../../../minishell.h"

static void if_char_dgreater_do(t_lexer *lexer, char *line)
{
    if (lexer->j > 0)
    {
        lexer->token->data[lexer->j] = 0;
        lexer->token->next = malloc(sizeof(t_tok));
        lexer->token = lexer->token->next;
        tok_init(lexer->token, lexer->size);
        lexer->j = 0;
    }
    lexer->token->data[0] = '>';
    lexer->token->data[1] = '>';
    lexer->token->data[2] = 0;
    lexer->token->type = lexer->chtype;
    if (*(line + 1) && *(line + 1) != '\n' && *(line + 1) != '\0')
    {
        lexer->token->next = malloc(sizeof(t_tok));
        lexer->token = lexer->token->next;
        tok_init(lexer->token, lexer->size);
    }
}

void if_state_in_general(t_lexer *lexer, char *line)
{
	if (lexer->chtype == CHAR_QUOTE)
		if_char_quote_do(lexer);
	else if (lexer->chtype == CHAR_DQUOTE)
		if_char_dquote_do(lexer);
	else if (lexer->chtype == CHAR_ESCAPESEQ || lexer->chtype == CHAR_GENERAL)
		if_char_escape_or_general_do(lexer, line);
	else if (lexer->chtype == CHAR_WHITESPACE)
		if_char_whitespace_do(lexer, line);
	else if (lexer->chtype == CHAR_SEMICOLON || lexer->chtype == CHAR_GREATER
	|| lexer->chtype == CHAR_LESSER || lexer->chtype == CHAR_PIPE)
	    if_semi_great_less_pipe_char_do(lexer, line);
	else if (lexer->chtype == CHAR_DGREATER)
	    if_char_dgreater_do(lexer, line);
}
