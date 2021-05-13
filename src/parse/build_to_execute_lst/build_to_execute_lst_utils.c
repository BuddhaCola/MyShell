/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_to_execute_lst_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igearhea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 17:03:39 by igearhea          #+#    #+#             */
/*   Updated: 2021/05/13 17:03:40 by igearhea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	parse_build(t_todo *all, t_cmds **cmds)
{
	all->to_execute = malloc(sizeof(t_to_execute));
	all->to_execute->cmds = malloc(sizeof(t_cmds));
	all->to_execute->cmds->cmd_str = NULL;
	all->to_execute->cmds->args = NULL;
	all->to_execute->cmds->input_files = NULL;
	all->to_execute->cmds->output_files = NULL;
	all->to_execute->cmds->append_files = NULL;
	all->to_execute->cmds->next = NULL;
	*cmds = all->to_execute->cmds;
}

void	init_cmds_elem(t_cmds *cmds)
{
	cmds->cmd_str = NULL;
	cmds->args = NULL;
	cmds->input_files = NULL;
	cmds->output_files = NULL;
	cmds->append_files = NULL;
	cmds->next = NULL;
}

t_cmds	*get_new_cmds_elem(t_cmds *cmds)
{
	cmds->next = malloc(sizeof(t_cmds));
	init_cmds_elem(cmds->next);
	return (cmds->next);
}

void	get_cmd_str(t_cmds *cmds, t_tok *tok)
{
	cmds->cmd_str = ft_strdup(tok->data);
	cmds->args = malloc(sizeof(char *) * 2);
	cmds->args[0] = ft_strdup(tok->data);
	cmds->args[1] = NULL;
}
