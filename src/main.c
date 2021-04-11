/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtaylor <wtaylor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 18:15:43 by wtaylor           #+#    #+#             */
/*   Updated: 2021/04/11 18:28:46 by wtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dumb_parse(t_todo todo)
{
	printf("dumb_parse\n");
}

void	dumb_exec(t_todo todo)
{
	printf("dumb_exec\n");
}

void	dumb_destroy(t_todo todo)
{
	printf("dumb_destroy\n");
}

int		main(int argc, char **argv, char **env)
{
	t_todo todo;

	//declare foo pointers
	void (*parse) (t_todo todo);
	void (*exec) (t_todo todo);
	void (*destroy) (t_todo todo);
	//init foo pointers
	parse = dumb_parse;
	exec = dumb_exec;
	destroy = dumb_destroy;
	//call foo's
	parse(todo);
	exec(todo);
	destroy(todo);
	return (0);
}