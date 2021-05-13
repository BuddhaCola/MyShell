/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igearhea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 17:07:39 by igearhea          #+#    #+#             */
/*   Updated: 2021/05/13 17:07:40 by igearhea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	if_ch_is_dquote_set_state_general(int *state, int *chtype)
{
	if (*chtype == CHAR_DQUOTE)
		*state = STATE_GENERAL;
}

void	get_chtype(char **line, int *chtype)
{
	char	*str;

	str = *line;
	if (*(str + 1) && ((*str == '>') && (*(str + 1) == '>')))
	{
		*chtype = CHAR_DGREATER;
		str++;
		*line = str;
	}
	else
		*chtype = get_num_of_type(*str);
}

void	init_tokenizer(t_lexer *lexer, int size)
{
	lexer->tok_list = malloc(sizeof(t_tok));
	lexer->token = lexer->tok_list;
	tok_init(lexer->token, size);
	lexer->chtype = 0;
	lexer->j = 0;
	lexer->state = STATE_GENERAL;
	lexer->size = size;
}

void	if_char_null_set_zero(t_lexer *lexer)
{
	if (lexer->chtype == CHAR_NULL || lexer->chtype == CHAR_NEWLINE)
	{
		if (lexer->j > 0)
		{
			lexer->token->data[lexer->j] = '\0';
			lexer->j = 0;
		}
	}
}

void	if_last_char_is_not_zero_do_line_pp(char **line)
{
	if (**line != '\0')
		*line = *line + 1;
}
