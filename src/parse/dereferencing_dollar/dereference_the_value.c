/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dereference_the_value.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igearhea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 17:05:08 by igearhea          #+#    #+#             */
/*   Updated: 2021/05/13 17:05:09 by igearhea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	if_general_do(t_todo *all)
{
	if (*(all->d_u.str) == '\\')
	{
		if (*(all->d_u.str + 1) == '\0' || *(all->d_u.str + 2) == '\0')
			all->d_u.break_flg = 1;
		else
			(all->d_u.str)++;
	}
	else if (*(all->d_u.str) == '$' && *(all->d_u.str + 1) != '\0'
		&& (ft_isalpha(*(all->d_u.str + 1))
			 || ft_strchr("?_", *(all->d_u.str + 1))))
		get_key(all);
	else if (*(all->d_u.str) == '\'')
		all->d_u.state = STATE_IN_QUOTE;
	else if (*(all->d_u.str) == '\"')
		all->d_u.state = STATE_IN_DQUOTE;
}

static void	if_dquote_do(t_todo *all)
{
	if (*(all->d_u.str) == '\\')
	{
		if (*(all->d_u.str + 1) == '\0' || *(all->d_u.str + 2) == '\0')
			all->d_u.break_flg = 1;
		else
			(all->d_u.str)++;
	}
	else if (*(all->d_u.str) == '$' && *(all->d_u.str + 1) != '\0'
		&& (ft_isalpha(*(all->d_u.str + 1))
			|| ft_strchr("?_", *(all->d_u.str + 1))))
		get_key(all);
	else if (*(all->d_u.str) == '\"')
		all->d_u.state = STATE_GENERAL;
}

static void	body(t_todo *all)
{
	if (all->d_u.state == STATE_GENERAL)
		if_general_do(all);
	else if (all->d_u.state == STATE_IN_QUOTE
		&& *(all->d_u.str) == '\'')
		all->d_u.state = STATE_GENERAL;
	else if (all->d_u.state == STATE_IN_DQUOTE)
		if_dquote_do(all);
}

static void	try_dereference(t_todo *all, char **src)
{
	all->d_u.str = *src;
	all->d_u.state = STATE_GENERAL;
	all->d_u.key = malloc(sizeof(char)
			* ft_strlen(all->d_u.str) + 1);
	all->d_u.break_flg = 0;
	all->d_u.src = src;
	while (*(all->d_u.str))
	{
		body(all);
		if (all->d_u.break_flg == 0)
			(all->d_u.str)++;
		else
			all->d_u.break_flg = 0;
	}
	free(all->d_u.key);
}

void	dereference_the_value(t_todo *all)
{
	t_pipelist	*pipe_elem;
	t_tok		*token;

	pipe_elem = all->parse_utils->pipelist;
	while (pipe_elem != NULL)
	{
		token = pipe_elem->tok_lst;
		while (token != NULL)
		{
			if (token->type == TOKEN)
				try_dereference(all, &(token->data));
			token = token->next;
		}
		pipe_elem = pipe_elem->next;
	}
}
