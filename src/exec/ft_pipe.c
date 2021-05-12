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
	int   pipeline[2];
	pid_t pid;
	int		fd_in = 0;
	int		filefd;

	int i = 0;
	int count_cmd = 0;
	int	exitcode;

	int orig1;

	t_cmds *cmds_cpy;
	cmds_cpy = all->to_execute->cmds;
	while(cmds_cpy)
	{
		count_cmd++;
		pipe(pipeline);
		pid = fork();
		if (pid == -1)
			exit (-1);
		else if (pid == 0)
		{
			dup2(fd_in, 0);
			close (fd_in);
			if (cmds_cpy->next != NULL)
				dup2(pipeline[1], 1);
			close(pipeline[0]);
			if (cmds_cpy->input_files)
				input_redirect(all);
			if (cmds_cpy->output_files)
			{
//					output_redirect(all);
//					dup2(pipeline[1], orig1);
//					close(pipeline[1]);
				filefd = open("output", OUTPUT_FILE, 0644);
				dup2(filefd, 1);
				close(filefd);
			}
			execvp(cmds_cpy->cmd_str, cmds_cpy->args);
			exit(EXIT_FAILURE);
		}
		else
		{
			close(pipeline[1]);
			fd_in = pipeline[0];
			cmds_cpy = cmds_cpy->next;
		}
	}
	while (i < count_cmd)
	{
		wait(&exitcode);
		i++;
	}
//	int ret;
//	if (WIFSIGNALED(exitcode))
//		ret = WTERMSIG(exitcode) + 128;
//	else if (WIFEXITED(exitcode))
//		ret = WEXITSTATUS(exitcode);
	return (exitcode);
}
