#include "../../../minishell.h"

void if_char_quote_do(t_lexer *lexer)
{
    lexer->state = STATE_IN_QUOTE;
    lexer->token->data[lexer->j++] = CHAR_QUOTE;
    lexer->token->type = TOKEN;
}

void if_char_dquote_do(t_lexer *lexer)
{
    lexer->state = STATE_IN_DQUOTE;
    lexer->token->data[lexer->j++] = CHAR_DQUOTE;
    lexer->token->type = TOKEN;
}

void if_char_escape_or_general_do(t_lexer *lexer, const char *line)
{
    lexer->token->data[lexer->j++] = *line;
    lexer->token->type = TOKEN;
}

void if_char_whitespace_do(t_lexer *lexer, const char *line)
{
    if (lexer->j > 0)
    {
        lexer->token->data[lexer->j] = 0;
        if (*(line + 1) && *(line + 1) != '\n' && *(line + 1) != '\0')
        {
            lexer->token->next = malloc(sizeof(t_tok));
            lexer->token = lexer->token->next;
            tok_init(lexer->token, lexer->size);
        }
        lexer->j = 0;
    }
}

void if_semi_great_less_pipe_char_do(t_lexer *lexer, const char *line)
{
    if (lexer->j > 0)
    {
        lexer->token->data[lexer->j] = 0;
        lexer->token->next = malloc(sizeof(t_tok));
        lexer->token = lexer->token->next;
        tok_init(lexer->token, lexer->size);
        lexer->j = 0;
    }
    lexer->token->data[0] = lexer->chtype;
    lexer->token->data[1] = 0;
    lexer->token->type = lexer->chtype;
    if (*(line + 1) && *(line + 1) != '\n' && *(line + 1) != '\0')
    {
        lexer->token->next = malloc(sizeof(t_tok));
        lexer->token = lexer->token->next;
        tok_init(lexer->token, lexer->size);
    }
}