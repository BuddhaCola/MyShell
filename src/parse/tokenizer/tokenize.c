#include "../../minishell.h"

/*
 * использовать лист токенов
 */
static int  get_num_of_type(char c)
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
	else if (c == 0)
		return (CHAR_NULL);
	return (CHAR_GENERAL);
}

static void tok_init(t_tok *tok, int data_size)
{
	tok->data = malloc(data_size + 1);
	tok->type = CHAR_NULL;
	tok->next = NULL;
}

static void		tok_destroy(t_tok *tok)
{
	if (tok != NULL)
	{
		free(tok->data);
		tok_destroy(tok->next);
		free(tok);
	}
}

static void get_chtype(char *line, int *i, int *chtype, char c)
{
	if (line[*i + 1] && ((line[*i] == '>') && (line[*i + 1] == '>')))
	{
		*chtype = CHAR_DGREATER;
		(*i)++;
	}
	else
		*chtype = get_num_of_type(c);
}

static int count_tokens(t_tok *token)
{
	int k;

	k = 0;
	while (token != NULL)
	{
		k++;
		token = token->next;
	}
	return (k);
}

int tokenize(char *line, int size, t_lexer *lexer_list)
{
	t_tok	*token;
	int		i;
	int		j;
	char    *save_tok_data_ptr;
	char	c;
	int		state;
	int		chtype;

	if (lexer_list == NULL)
		return -1;
	lexer_list->num_of_tokens = 0;
	if (size == 0)
		return 0;
	lexer_list->tok_list = malloc(sizeof(t_tok));
	token = lexer_list->tok_list;
	tok_init(token, size);
	i = 0;
	j = 0;
	state = STATE_GENERAL;
	while (1)
	{
		c = line[i];

		//get chtype
		get_chtype(line, &i, &chtype, c);

		//if general
		if (state == STATE_GENERAL)
		{
			if (chtype == CHAR_QUOTE)
			{
				state = STATE_IN_QUOTE;
				token->data[j++] = CHAR_QUOTE;
				token->type = TOKEN;
			}
			if (chtype == CHAR_DQUOTE)
			{
				state = STATE_IN_DQUOTE;
				token->data[j++] = CHAR_DQUOTE;
				token->type = TOKEN;
			}
			if (chtype == CHAR_ESCAPESEQ)
			{
				token->data[j++] = c;
				token->type = TOKEN;
			}
			if (chtype == CHAR_GENERAL)
			{
				token->data[j++] = c;
				token->type = TOKEN;
			}
			if (chtype == CHAR_WHITESPACE)
			{
				if (j > 0)
				{
					token->data[j] = 0;
					if (line[i + 1] && line[i + 1] != '\n' && line[i + 1] != '\0')
					{
						token->next = malloc(sizeof(t_tok));
						token = token->next;
						tok_init(token, size - i);
					}
					j = 0;
				}
			}
			if (chtype == CHAR_SEMICOLON || chtype == CHAR_GREATER || chtype == CHAR_LESSER || chtype == CHAR_AMPERSAND
			|| chtype == CHAR_PIPE)
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
				if (line[i + 1] && line[i + 1] != '\n' && line[i + 1] != '\0')
				{
					token->next = malloc(sizeof(t_tok));
					token = token->next;
					tok_init(token, size - i);
				}
			}
			if (chtype == CHAR_DGREATER)
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
				token->data[2] = 0;
				token->type = chtype;
				if (line[i + 1] && line[i + 1] != '\n' && line[i + 1] != '\0')
				{
					token->next = malloc(sizeof(t_tok));
					token = token->next;
					tok_init(token, size - i);
				}
			}
		}
		//else if state in quote
		else if (state == STATE_IN_QUOTE)
		{
			token->data[j++] = c;
			if (chtype == CHAR_QUOTE)
				state = STATE_GENERAL;
		}
		//else if state in dquote
		else if (state == STATE_IN_DQUOTE)
		{
			token->data[j++] = c;
			if (chtype == CHAR_DQUOTE)
				state = STATE_GENERAL;
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
	lexer_list->num_of_tokens = count_tokens(lexer_list->tok_list);
	return (lexer_list->num_of_tokens);
}

void		lexer_destroy(t_lexer *list)
{
	if (list == NULL)
		return ;
	tok_destroy(list->tok_list);
}
