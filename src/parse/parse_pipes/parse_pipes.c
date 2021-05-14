/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igearhea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 17:05:53 by igearhea          #+#    #+#             */
/*   Updated: 2021/05/13 17:05:54 by igearhea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	if_pipe_do(t_pipelist **pipelist, t_tok **pipe_lst_tok)
{
	*pipelist = get_next_pipe_list_elem(*pipelist);
	*pipe_lst_tok = (*pipelist)->tok_lst;
}

static void	if_semi_do(t_todo *all, t_tok *src_lst)
{
	if (src_lst->next == NULL)
		all->parse_utils->cur_tok = src_lst->next;
	else
		all->parse_utils->cur_tok = src_lst;
}

static void	set_data_and_type(t_tok *src_lst, t_tok *pipe_lst_tok)
{
	pipe_lst_tok->data = ft_strdup(src_lst->data);
	pipe_lst_tok->type = src_lst->type;
}

void	parse_pipes(t_todo *all)
{
	t_tok		*src_lst;
	t_tok		*pipe_lst_tok;
	t_pipelist	*pipelist;

	init_pipe_list(all, &src_lst, &pipe_lst_tok, &pipelist);
	while (src_lst)
	{
		if (src_lst->type == CHAR_PIPE)
			if_pipe_do(&pipelist, &pipe_lst_tok);
		else if (src_lst->type == CHAR_SEMICOLON)
		{
			if_semi_do(all, src_lst);
			break ;
		}
		else
		{
			set_data_and_type(src_lst, pipe_lst_tok);
			if (src_lst->next != NULL && src_lst->next->type != CHAR_PIPE
				&& src_lst->next->type != CHAR_SEMICOLON)
				pipe_lst_tok = get_next_tok_list_elem(pipe_lst_tok);
		}
		src_lst = src_lst->next;
		if (!src_lst)
			all->parse_utils->cur_tok = src_lst;
	}
}
