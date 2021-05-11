/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtaylor <wtaylor@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:42:24 by wtaylor           #+#    #+#             */
/*   Updated: 2021/04/19 17:42:26 by wtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
int	redirection(char *filepath, char *program, char **args, int mode)
{
	int		filefd;
	int		pid;

	if (mode == 0) // '>'
		filefd = open(filepath, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else if (mode == 1) // ">>"
		filefd = open(filepath, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (mode == 2) // '<'
		filefd = open(filepath, O_RDONLY, 0644);
	if (filefd < 0)
		return (1);
	pid = fork();
	if (!pid)
	{
		if (mode == 2)
			dup2(filefd, STDIN_FILENO);
		else
			dup2(filefd, STDOUT_FILENO);
		execve(program, args, 0);
		return (0);
	}
	else
		waitpid(pid, 0, 0);
	close(filefd);
	return (0);
}
