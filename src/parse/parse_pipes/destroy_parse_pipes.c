/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_parse_pipes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igearhea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 17:05:23 by igearhea          #+#    #+#             */
/*   Updated: 2021/05/13 17:05:24 by igearhea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	delete_tokens(t_tok *tok_elem)
{
	if (tok_elem != NULL)
	{
		free(tok_elem->data);
		delete_tokens(tok_elem->next);
		free(tok_elem);
	}
}

static void	delete_all_tokens_in_pipe_lst(t_todo *all)
{
	t_pipelist	*pipe_elem;

	pipe_elem = all->parse_utils->pipelist;
	while (pipe_elem)
	{
		delete_tokens(pipe_elem->tok_lst);
		pipe_elem = pipe_elem->next;
	}
}

static void	delete_all_pipe_elems(t_pipelist *pipe_elem)
{
	if (pipe_elem != NULL)
	{
		delete_all_pipe_elems(pipe_elem->next);
		free(pipe_elem);
	}
}

void	destroy_parse_pipes(t_todo *all)
{
	delete_all_tokens_in_pipe_lst(all);
	delete_all_pipe_elems(all->parse_utils->pipelist);
}
