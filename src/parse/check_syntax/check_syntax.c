#include "../../minishell.h"

static char *build_error_str(char *str, char *token_data)
{
    char *ret;
    char *tmp;
    tmp = ft_strjoin(str, token_data);
    ret = ft_strjoin(tmp, "'");
    free(tmp);
    return (ret);
}

static void print_error_unexpctd_near_tok(t_todo *all, t_tok *token)
{
    char *err_str;
    err_str = build_error_str("syntax error near unexpected token '", token->data);
    errorhandle(all, NULL, err_str, "1");
    free(err_str);
}

int check_syntax(t_todo *all, t_tok *token)
{
	t_tok *previous_token;
	char *err_str;

	previous_token = token;
	//iterate tokens
	while (token)
	{
		if (validate_quotation(token->data))
		{
			errorhandle(all, NULL, "syntax error, quotes not closed", "1");
			return (-1);
		}
		if (((token->type == CHAR_GREATER || token->type == CHAR_DGREATER || token->type == CHAR_LESSER)
		&& (previous_token->type != TOKEN || token->next == NULL || token->next->type != TOKEN))
		|| (token->type == CHAR_PIPE && (previous_token->type != TOKEN
		|| token->next == NULL || token->next->type != TOKEN))
		|| (token->type == CHAR_SEMICOLON && previous_token->type != TOKEN))
		{
            print_error_unexpctd_near_tok(all, token);
            return (-1);
		}
		previous_token = token;
		token = token->next;
	}
	return (0);
}
