#include "../../minishell.h"

static int set_and_return_num_of_tokens(t_lexer *lexer)
{
	lexer->num_of_tokens = count_tokens(lexer->tok_list);
	return lexer->num_of_tokens;
}

static void if_state_in_quote(t_lexer *lexer, const char *line)
{
	lexer->token->data[lexer->j++] = *line;
	if_ch_is_quote_set_state_general(&lexer->state, &lexer->chtype);
}

static void if_state_in_dquote(t_lexer *lexer, const char *line)
{
	lexer->token->data[lexer->j++] = *line;
	if_ch_is_dquote_set_state_general(&lexer->state, &lexer->chtype);
}

int tokenize(char *line, int size, t_lexer *lexer)
{
	init_tokenizer(lexer, size);
	while (*line)
	{
		get_chtype(&line, &lexer->chtype);
		if (lexer->state == STATE_GENERAL)
			if_state_in_general(lexer, line);
		else if (lexer->state == STATE_IN_QUOTE)
			if_state_in_quote(lexer, line);
		else if (lexer->state == STATE_IN_DQUOTE)
			if_state_in_dquote(lexer, line);
		if_char_null_set_zero(lexer);
		if_last_char_is_not_zero_do_line_pp(&line);
	}
	return (set_and_return_num_of_tokens(lexer));
}
