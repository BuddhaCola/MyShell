/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtaylor <wtaylor@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 15:24:57 by wtaylor           #+#    #+#             */
/*   Updated: 2021/04/14 15:25:00 by wtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
int	ft_pipe(char *program1, char *program2)
{
	int	pipes[2];
	int	process1;
	int	process2;

	if (pipe(pipes) == -1)
		return (2);
	process1 = fork();
	if (process1 == 0)
	{
		dup2(pipes[1], STDOUT_FILENO);
		close(pipes[0]);
		close(pipes[1]);
		execve(program1, 0, 0);
	}
	else if (process1 == -1)
		return (1);
	process2 = fork();
	if (process2 == 0)
	{
		dup2(pipes[0], STDIN_FILENO);
		close(pipes[0]);
		close(pipes[1]);
		execve(program2, 0, 0);
	}
	else if (process2 == -1)
		return (1);
	close(pipes[0]);
	close(pipes[1]);
	waitpid(process1, 0, 0);
	waitpid(process2, 0, 0);
	return (0);
}
