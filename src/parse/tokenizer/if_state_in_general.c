#include "../../minishell.h"

static void if_char_quote_do(t_lexer *lexer)
{
	lexer->state = STATE_IN_QUOTE;
	lexer->token->data[lexer->j++] = CHAR_QUOTE;
	lexer->token->type = TOKEN;
}

static void if_char_dquote_do(t_lexer *lexer)
{
	lexer->state = STATE_IN_DQUOTE;
	lexer->token->data[lexer->j++] = CHAR_DQUOTE;
	lexer->token->type = TOKEN;
}

static void if_char_escape_or_general_do(t_lexer *lexer, const char *line)
{
	lexer->token->data[lexer->j++] = *line;
	lexer->token->type = TOKEN;
}

static void if_char_whitespace_do(t_lexer *lexer, const char *line)
{
	if (lexer->j > 0)
	{
		lexer->token->data[lexer->j] = 0;
		if (*(line + 1) && line[i + 1] != '\n' && line[i + 1] != '\0')
		{
			token->next = malloc(sizeof(t_tok));
			token = token->next;
			tok_init(token, size - i);
		}
		j = 0;
	}
}

void if_state_in_general(t_lexer *lexer, char *line)
{
	if (lexer->chtype == CHAR_QUOTE)
		if_char_quote_do(lexer);
	if (lexer->chtype == CHAR_DQUOTE)
		if_char_dquote_do(lexer);
	if (lexer->chtype == CHAR_ESCAPESEQ || lexer->chtype == CHAR_GENERAL)
		if_char_escape_or_general_do(lexer, line);
	if (lexer->chtype == CHAR_WHITESPACE)
		if_char_whitespace_do(lexer, line);
	if (lexer->chtype == CHAR_SEMICOLON || lexer->chtype == CHAR_GREATER
	|| lexer->chtype == CHAR_LESSER || lexer->chtype == CHAR_PIPE)
	if (lexer->chtype == CHAR_DGREATER)
}
