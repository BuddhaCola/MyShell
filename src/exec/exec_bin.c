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

static int is_builtin(char *path)
{
	char *builtins[8];
	int i;

	i = 0;
	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "pwd";
	builtins[3] = "export";
	builtins[4] = "unset";
	builtins[5] = "env";
	builtins[6] = "exit";
	builtins[7] = NULL;
	while (builtins[i])
	{
		if (!(ft_strcmp(path, builtins[i++])))
		{ return (1); }
	}
	return (0);
}

static int do_builtin(char *path, t_todo *all)
{
	if (!(ft_strcmp(path, "echo")))
		ft_putstr_fd(path, 1);
	else if (!(ft_strcmp(path, "cd")))
		ft_putstr_fd(path, 1);
	else if (!(ft_strcmp(path, "pwd")))
		ft_putstr_fd(path, 1);
	else if (!(ft_strcmp(path, "export")))
		ft_putstr_fd(path, 1);
	else if (!(ft_strcmp(path, "unset")))
		ft_putstr_fd(path, 1);
	else if (!(ft_strcmp(path, "env")))
		ft_putstr_fd(path, 1);
	else if (!(ft_strcmp(path, "exit")))
		ft_exit(all->simple_command_list->cmd->args, all);
	else
		return (-1);
	ft_putstr_fd(" under construction! 🚧\n", 1);
	return (0);
}

int is_it_in_curdir(char *path)
{
	DIR				*current_dir;
	struct dirent	*current_file;

	current_dir = opendir(".");
	while ((current_file = readdir(current_dir)))
	{
		ft_putstr_fd("|", 1);
		ft_putstr_fd(current_file->d_name, 1);
		ft_putstr_fd("| ", 1);
	}
	ft_putstr_fd("\n", 1);
//		if (ft_strcmp(path, current_file->d_name))
}

int	exec_bin(char *path, t_todo *all)
{
	pid_t pid;

	if (is_builtin(path))
	{
		do_builtin(path, all);
		return (0);
	}
	if (!path)
	{
		ft_putstr_fd("command not found 😑\n", 1);
		return (-1);
	}
	pid = fork();
	if (!pid)
	{
		ft_putstr_fd("|executing |", 1);
		ft_putstr_fd(path, 1);
		ft_putstr_fd("|!🏋️‍\n ", 1);
		all->exec.err = execve(all->simple_command_list->cmd->cmd_str,
						all->simple_command_list->cmd->args, NULL);
	}
	else
		wait(&pid);
	return (1);
}
