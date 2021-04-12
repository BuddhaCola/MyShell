/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtaylor <wtaylor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 18:15:43 by wtaylor           #+#    #+#             */
/*   Updated: 2021/04/12 14:54:44 by wtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		shell(t_todo *all)
{
	char	*buf;
	
	while (1)
	{
		write(1, "minishell 👉 ", 15);
		get_next_line(0, &buf);
		// parse(buf);
	}
	return (0);
}

int		main(int argc, char **argv, char **env)
{
	int		ret;
	t_todo	all;

	all.exec.env = env;
	char *envp = ft_dollarsign(" ", &all);
	printf("%s\n", envp);

	// ret = fork();
	// if (!ret)
	// {
	// 	all.exec.env = env;
	// 	shell(&all);
	// }
	// else
	// 	wait(&ret);
	return (0);
}