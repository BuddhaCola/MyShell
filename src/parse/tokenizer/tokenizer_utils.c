/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igearhea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 17:07:33 by igearhea          #+#    #+#             */
/*   Updated: 2021/05/13 17:07:34 by igearhea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int 	get_num_of_type(char c)
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

void	tok_init(t_tok *tok, int data_size)
{
	tok->data = malloc(data_size + 1);
	tok->type = CHAR_NULL;
	tok->next = NULL;
}

void	tok_destroy(t_tok *tok)
{
	if (tok != NULL)
	{
		free(tok->data);
		tok_destroy(tok->next);
		free(tok);
	}
}

int	count_tokens(t_tok *token)
{
	int	k;

	k = 0;
	while (token != NULL)
	{
		k++;
		token = token->next;
	}
	return (k);
}

void	if_ch_is_quote_set_state_general(int *state, int *chtype)
{
	if (*chtype == CHAR_QUOTE)
		*state = STATE_GENERAL;
}
