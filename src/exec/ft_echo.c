/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtaylor <wtaylor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 13:39:20 by wtaylor           #+#    #+#             */
/*   Updated: 2021/04/12 17:21:58 by wtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int 	ft_echo(t_todo *all)
{
	char	endsymbol;
	int		i;

	endsymbol = '\n';
	if (all->cur_cmd_list->args[0])
	{
		i = 1;
		if (!(ft_strcmp(all->cur_cmd_list->args[i], "-n")))
		{
			endsymbol = 0;
			i++;
		}
		while (all->cur_cmd_list->args[i])
		{
			write(1, all->cur_cmd_list->args[i],
				ft_strlen(all->cur_cmd_list->args[i]));
			i++;
			if (all->cur_cmd_list->args[i])
				write(1, " ", 1);
		}
	}
	write(1, &endsymbol, 1);
	return (0);
}
