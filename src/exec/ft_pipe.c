/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtaylor <wtaylor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 15:24:57 by wtaylor           #+#    #+#             */
/*   Updated: 2021/04/18 21:53:48 by wtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pipe(t_todo *all)
{
	int   p[2];
	pid_t pid;
	int		fd_in = 0;
	int		filefd;

	t_cmds *cmds_cpy;
	cmds_cpy = all->to_execute->cmds;
	while(cmds_cpy)
	{
		pipe(p);
		if ((pid = fork()) == -1)
		{
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			if (cmds_cpy->input_files)
			{
				PROBE
				filefd = open(*cmds_cpy->input_files, O_RDONLY, 0777);
				dup2(filefd, STDIN_FILENO);
				cmds_cpy->input_files++;
			}
			else
				dup2(fd_in, 0); //change the input according to the old one
			if (cmds_cpy->next != NULL)
				dup2(p[1], 1);
			close(p[0]);
			execvp(cmds_cpy->cmd_str, cmds_cpy->args);
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(NULL);
			close(p[1]);
			fd_in = p[0]; //save the input for the next command
			cmds_cpy = cmds_cpy->next;
		}
	}
	return (0);
}
