/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detroy_to_excute_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igearhea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 17:03:58 by igearhea          #+#    #+#             */
/*   Updated: 2021/05/13 17:04:03 by igearhea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	destroy_2d(char **str)
{
	char	**str_cpy;

	str_cpy = str;
	if (str != NULL)
	{
		while (*str != NULL)
		{
			free(*str);
			str++;
		}
		free(str_cpy);
	}
}

static void	destroy_cmds(t_cmds *cmds)
{
	if (cmds != NULL)
	{
		if (cmds->cmd_str != NULL)
			free(cmds->cmd_str);
		destroy_2d(cmds->args);
		destroy_2d(cmds->input_files);
		destroy_2d(cmds->output_files);
		destroy_2d(cmds->append_files);
		destroy_cmds(cmds->next);
		free(cmds);
	}
}

void	destroy_to_execute_lst(t_todo *all)
{
	destroy_cmds(all->to_execute->cmds);
	free(all->to_execute);
}
