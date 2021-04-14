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

void test_parse(char *buf, t_todo *all)
{
	int i = -1;
	while (buf[++i])
	{
		if (buf[i] == '$')
		{
			i++;
			char *envp;
			if (!(envp = ft_dollarsign(&buf[i], all)))
				envp = "";
			printf("%s\n", envp);
		}
		else if (buf[i] == '!')
			exec_bin(&buf[i+1], all);
		else if (buf[i] == '?')
			printf("%d\n", all->exec.err);
		else if (buf[i] == '|')
		{
			char **args = ft_split(&buf[i+1], ' ');
			ft_pipe(args[0], args[1]);
		}
	}
}

int		shell(t_todo *all)
{
	char	*buf;
	
	while (1)
	{
		write(1, "minishell 👉 ", 15);
		get_next_line(0, &buf);
		test_parse(buf, all);
	}
	return (0);
}

int		main(int argc, char **argv, char **env)
{
	pid_t		ret;
	t_todo		all;

	 ret = fork();

	 if (!ret)
	 {
	 	all.exec.env = env;
	 	shell(&all);
	 }
	 else
	 {
	 	write(1, "⌚️ I'm waiting.\n", 20);
	 	wait(&ret);
	 }
	 write(1, "👋 exiting\n", 13);
	return (0);
}