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

//static int	go_through_redirections(t_todo *all, char ***type, int mode)
//{
//	int	filefd;
//
//	while (*type && **type)
//	{
//		filefd = open(**type, mode, 0644);
//		if (filefd == -1)
//		{
//			ft_putendl_fd("failed to open!", 1);
//			return (-1);
//		}
//		(*type)++;
//	}
//	return (filefd);
//}

//int	ft_pipe(t_todo *all)
//{
//	int p[2];
//	pid_t pid;
//	int fd_in;
//	int filefd;
//
//	t_cmds *cmds_cpy;
//	cmds_cpy = all->to_execute->cmds;
//	fd_in = 0;
//	while (cmds_cpy)
//	{
//		pipe(p);
//		if ((pid = fork()) == -1)
//		{
//			exit(EXIT_FAILURE);
//		}
//		else if (pid == 0)
//		{
//			dup2(fd_in, 0);
//			close(fd_in);
//			if (cmds_cpy->next != NULL)
//				dup2(p[1], 1);
//			close(p[0]);
//			if (cmds_cpy->input_files)
//				input_redirect(all);
//			if (cmds_cpy->output_files)
//				output_redirect(all);
//			execvp(cmds_cpy->cmd_str, cmds_cpy->args);
//			exit(EXIT_FAILURE);
//		}
//		else
//		{
//			wait(NULL);
//			close(p[1]);
//			fd_in = p[0];
//			cmds_cpy = cmds_cpy->next;
//		}
//	}
//}

int	ft_pipe(t_todo *all)
{
	int		pipeline[2];
	pid_t	pid;
	int		fd_in;
	int		filefd;

	int i = 0;
	int count_cmd = 0;
	int	exitcode;
	fd_in = -1;

	int	fd_to_close[20];

//	t_cmds *cmds_cpy;
//	cmds_cpy = all->cur_cmds;
	while(all->cur_cmds)
	{
		count_cmd++;
		pipe(pipeline);

		pid = fork();
		if (pid == -1)
			exit (-1);
		else if (pid == 0)
		{
//			if (!all->cur_cmds->next)
			if (fd_in > 0)
			{
				dup2(fd_in, 0);
				close(fd_in);
			}
			if (all->cur_cmds->next != NULL)
				dup2(pipeline[1], 1);
			close(pipeline[0]);
			close(pipeline[1]);
			if (all->cur_cmds->input_files)
				input_redirect(all);
			if (all->cur_cmds->output_files)
				if (output_redirect(all) == -1)
					return (-1);
			execve(all->cur_cmds->cmd_str, all->cur_cmds->args, all->environments);
			exit(EXIT_FAILURE);
		}
		else
		{
			close(pipeline[1]);
//			if (!all->cur_cmds->next)
//			{
//				close(pipeline[0]);
//				pipeline[0] = 0;
//			}
			close(fd_in);
			fd_in = dup(pipeline[0]);
			close(pipeline[0]);
			all->cur_cmds = all->cur_cmds->next;
		}
//		if (pipeline[0] && cmds_cpy->next)
//			close(pipeline[0]);
	}
	close(fd_in);
	while (i < count_cmd)
	{
		wait(&exitcode);
		i++;
	}
	return (exitcode);
}


//	int ret;
//	if (WIFSIGNALED(exitcode))
//		ret = WTERMSIG(exitcode) + 128;
//	else if (WIFEXITED(exitcode))
//		ret = WEXITSTATUS(exitcode);