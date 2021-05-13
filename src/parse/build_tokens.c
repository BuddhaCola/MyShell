/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igearhea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 17:07:51 by igearhea          #+#    #+#             */
/*   Updated: 2021/05/13 17:07:53 by igearhea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	build_tokens(t_todo *all, char *line, int size
		, t_lexer *lexer_list)
{
	tokenize(line, size, lexer_list);
	if (check_syntax(all, lexer_list->tok_list))
	{
		lexer_destroy(all->lex_buf);
		all->parse_utils = malloc(sizeof(t_parse_utils));
		return (-1);
	}
	all->parse_utils = malloc(sizeof(t_parse_utils));
	all->parse_utils->cur_tok = all->lex_buf->tok_list;
	return (0);
}
