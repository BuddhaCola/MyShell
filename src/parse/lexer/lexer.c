/*
 * Вернемся к восстановлению
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */

#include "../../minishell.h"

int	get_num_of_type(char c)
{
	if (c == ' ')
		return (CHAR_WHITESPACE);
	else if (c == ';')
		return (CHAR_SEMICOLON);
	else if (c == '\'')
		return (CHAR_QUOTE);
	else if (c == '\"')
		return (CHAR_DQUOTE);
	else if (c == '|')
		return (CHAR_PIPE);
	else if (c == '&')
		return (CHAR_AMPERSAND);
	else if (c == '\\')
		return (CHAR_ESCAPESEQ);
	else if (c == '\t')
		return (CHAR_TAB);
	else if (c == '\n')
		return (CHAR_NEWLINE);
	else if (c == '>')
		return (CHAR_GREATER);
	else if (c == '<')
		return (CHAR_LESSER);
	else if (c == '$')
        return (CHAR_DOLLAR);
	else if (c == 0)
		return (CHAR_NULL);
	return (CHAR_GENERAL);
}

void		tok_init(t_tok *tok, int data_size)
{
	tok->data = malloc(data_size + 1);
	tok->type = CHAR_NULL;
	tok->next = NULL;
}

void		tok_destroy(t_tok *tok)
{
	if (tok != NULL)
	{
		free(tok->data);
		tok_destroy(tok->next);
		free(tok);
	}
}

int			lexer_build(char *line, int size, t_lexer *lexer_list)
{
	t_tok	*token;
	int		i;
	int		j;
	char    *save_tok_data_ptr;
	char	c;
	int		state;
	int		chtype;
	int		k;

	if (lexer_list == NULL)
		return -1;
	if (size == 0)
	{
		lexer_list->num_of_tokens = 0;
		return 0;
	}
	lexer_list->tok_list = malloc(sizeof(t_tok));
	token = lexer_list->tok_list;
	tok_init(token, size);
	i = 0;
	j = 0;
	state = STATE_GENERAL;
	while (1)
	{
		c = line[i];
		//if ">>" get type
        if (line[i + 1] && ((line[i] == '>') && (line[i + 1] == '>')))
        {
            chtype = CHAR_DGREATER;
            i++;
        }
        else
		    chtype = get_num_of_type(c);
		if (state == STATE_GENERAL || state == STATE_IN_DQUOTE)
		{
		    if (chtype == CHAR_QUOTE)
			{
		        if ((i != 0) && ((line[i - 1] == '\\') || (state == STATE_IN_DQUOTE)))
                {
                    token->data[j++] = CHAR_QUOTE;
                    token->type = TOKEN;
                }
		        else
                {
                    state = STATE_IN_QUOTE;
                    token->type = TOKEN;
                }
			}
			else if (chtype == CHAR_DQUOTE)
			{
			    if((i != 0) && (line[i - 1] == '\\'))
                {
                    token->data[j++] = CHAR_DQUOTE;
                    token->type = TOKEN;
                }
			    else
                {
			        if (state != STATE_IN_DQUOTE)
			        {
                        state = STATE_IN_DQUOTE;
                        token->type = TOKEN;
                    }
			        else
                    {
			            state = STATE_GENERAL;
                    }
                }
			}
			else if (chtype == CHAR_ESCAPESEQ)
			{
                token->data[j++] = line[i++];
                token->data[j++] = line[i];
                token->type = TOKEN;
			}
			else if (chtype == CHAR_GENERAL)
			{
				token->data[j++] = c;
				token->type = TOKEN;
			}
			else if (chtype == CHAR_WHITESPACE)
			{
				if (j > 0 && state != STATE_IN_DQUOTE)
				{
					token->data[j] = 0;
					token->next = malloc(sizeof(t_tok));
					token = token->next;
					tok_init(token, size - i);
					j = 0;
				}
				else if (state == STATE_IN_DQUOTE)
                {
                    token->data[j++] = c;
                }
			}
			else if ((chtype == CHAR_SEMICOLON) || (chtype == CHAR_GREATER) || (chtype == CHAR_LESSER) || (chtype == CHAR_AMPERSAND)
			|| (chtype == CHAR_PIPE))
			{
				if (j > 0)
				{
					token->data[j] = 0;
					token->next = malloc(sizeof(t_tok));
					token = token->next;
					tok_init(token, size - i);
					j = 0;
				}
				token->data[0] = chtype;
				token->data[1] = 0;
				token->type = chtype;
				token->next = malloc(sizeof(t_tok));
				token = token->next;
				tok_init(token, size - i);
			}
			else if (chtype == CHAR_DGREATER)
            {
                if (j > 0)
                {
                    token->data[j] = 0;
                    token->next = malloc(sizeof(t_tok));
                    token = token->next;
                    tok_init(token, size - i);
                    j = 0;
                }
                token->data[0] = '>';
                token->data[1] = '>';
                token->data[2] = '\0';
                token->type = chtype;
                token->next = malloc(sizeof(t_tok));
                token = token->next;
                tok_init(token, size - i);
            }
			else if (chtype == CHAR_DOLLAR)
			{
                if ((i != 0) && (line[i - 1] != '\\'))
                {
//                    dereference_the_value(line, &i);
                    token->type = TOKEN;
                }
                else
                {
                    token->data[j++] = c;
                    token->type = TOKEN;
                }
            }
		}
		else if (state == STATE_IN_QUOTE)
		{
		    if (c != '\'') //c == '
		    {
                token->data[j++] = c;
            }
		    else
            {
		        state = STATE_GENERAL;
            }
		}
		if (chtype == CHAR_NULL)
		{
			if (j > 0)
			{
				token->data[j] = 0;
				j = 0;
			}
		}
		if (c == '\0')
			break ;
		i++;
	}

	// count tokens
	token = lexer_list->tok_list;
	k = 0;
	while (token != NULL)
	{
		if (token->type == TOKEN)
		{
//		    strip_quotes(&save_tok_data_ptr, token->data);
//		    free(token->data);
//		    token->data = save_tok_data_ptr;
		    k++;
		}
		token = token->next;
	}
	lexer_list->num_of_tokens = k;
	return k;
}

static void		lexer_destroi(t_lexer *list)
{
	if (list == NULL)
		return ;
	tok_destroy(list->tok_list);
}
