#include "../../minishell.h"

//DONE
//check each token at the closed quotes
static int validate_quotation(char *str)
{
	int state;
	int state_general;
	int state_q;
	int state_dq;

	state_general = 0;
	state_q = 1;
	state_dq = 2;

	state = state_general;
	while (*str)
	{
		if (state == state_general)
		{
			if (*str == '\\')
			{
				if (*(str + 1) == '\0' || *(str + 2) == '\0')
					break;
				str += 2;
				continue;
			}
			if (*str == '\'')
				state = state_q;
			if (*str == '\"')
				state = state_dq;
		}
		else if (state == state_q)
		{
			if (*str == '\'')
				state = state_general;
		}
		else if (state == state_dq)
		{
			if (*str == '\\')
			{
				if (*(str + 1) == '\0' || *(str + 2) == '\0')
					break;
				str += 2;
				continue;
			}
			if (*str == '\"')
				state = state_general;
		}
		str++;
	}
	if (state != state_general)
		return (-1);
	return (0);
}

int check_syntax(t_todo *all, t_tok *token)
{
	t_tok *previous_token;
	char *err_str;
	char *save_str;

	previous_token = token;
	//iterate tokens
	while (token)
	{
		if (validate_quotation(token->data))
		{
			errorhandle(all, NULL, "bash: syntax error, quotes not closed", "1");
			return -1;
		}
		if (token->type == CHAR_GREATER || token->type == CHAR_DGREATER || token->type == CHAR_LESSER)
		{
			if (previous_token->type != TOKEN || token->next == NULL
			|| token->next->type != TOKEN)
			{
				save_str = ft_strjoin("bash: syntax error near unexpected token '", token->data);
				err_str = ft_strjoin(save_str, "'");
				free(save_str);
				errorhandle(all, NULL, err_str, "1");
				free(err_str);
				return -1;
			}
		}
		if (token->type == CHAR_PIPE)
		{
			if (previous_token->type != TOKEN || token->next == NULL
				|| token->next->type != TOKEN)
			{
				save_str = ft_strjoin("bash: syntax error near unexpected token '", token->data);
				err_str = ft_strjoin(save_str, "'");
				free(save_str);
				errorhandle(all, NULL, err_str, "1");
				free(err_str);
				return -1;
			}
		}
		if (token->type == CHAR_SEMICOLON)
		{
			if (previous_token->type != TOKEN)
			{
				save_str = ft_strjoin("bash: syntax error near unexpected token '", token->data);
				err_str = ft_strjoin(save_str, "'");
				free(save_str);
				errorhandle(all, NULL, err_str, "1");
				free(err_str);
				return -1;
			}
		}
		previous_token = token;
		token = token->next;
	}
	return (0);
}
