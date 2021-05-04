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
		ft_putstr_fd("echo", 1);
	else if (!(ft_strcmp(path, "cd")))
		ft_putstr_fd("cd", 1);
	else if (!(ft_strcmp(path, "pwd")))
	{
		ft_putstr_fd(getenv("PWD"), 1);
		ft_putstr_fd("\n", 1);
		return (1);
	}
	else if (!(ft_strcmp(path, "export")))
		return (ft_export(all));
	else if (!(ft_strcmp(path, "unset")))
		return (ft_unset(all));
	else if (!(ft_strcmp(path, "env")))
	{
		return (ft_env(all));
	}
	else if (!(ft_strcmp(path, "exit")))
		ft_exit(all->to_execute->cmd->args, all);
	else
		return (0);
	ft_putstr_fd(" under construction! 🚧\n", 1);
	return (0);
}

int	exec_bin(char *path, t_todo *all)
{
	pid_t pid;

	if (do_builtin(path, all) != 0)
		return (all->exit_code);
	if (!path)
	{
		ft_putstr_fd("bash: ", 1);
		ft_putstr_fd(all->to_execute->cmd->cmd_str, 1);
		ft_putstr_fd(": command not found 😑\n", 1);
		return (-1);
	}
	free(path);
	pid = fork();
	if (!pid)
	{
		all->exec.err = execve(all->to_execute->cmd->cmd_str,
						all->to_execute->cmd->args, all->environments);
	}
	else
		wait(&pid);
	return (1);
}
