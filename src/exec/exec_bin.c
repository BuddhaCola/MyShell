/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtaylor <wtaylor@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 17:34:48 by wtaylor           #+#    #+#             */
/*   Updated: 2021/04/13 17:34:49 by wtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_bin(char *path, t_todo *all)
{
	pid_t pid;

	pid = fork();
	if (!pid)
		all->exec.errno = execve(path, NULL, NULL);
	else
		wait(&pid);
	return (1);
}