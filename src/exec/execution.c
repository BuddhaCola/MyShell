#include "../minishell.h"

int	start_process(t_todo *all, char *bin)
{
	pid_t	pid;

	pid = fork();
	if (!pid)
		execve(bin, all->to_execute->cmds->args, all->environments);
	else
	{
		errno = 0;
		wait(&(all->exit_code));
		all->exit_code /= 255;
		if (all->exit_code < 0)
			errorhandle(all, all->to_execute->cmds->cmd_str, NULL, NULL);
		free(bin);
	}
	return (all->exit_code);
}

//int	define_and_execute(t_todo *all)
//{
//	int		try;
//	char	*bin_location;
//
//	if (ft_strchr("./", all->to_execute->cmds->cmd_str[0]))
//	{
//		try = try_rel_abs_path(all);
//		if (try)
//			return (try);
//	}
//	if (is_builtin(all->to_execute->cmds->cmd_str))
//		return (do_builtin(all->to_execute->cmds->cmd_str, all));
//	bin_location = try_path(all);
//	if (bin_location)
//		return (start_process(all, bin_location));
//	else
//	{
//		errorhandle(all, all->to_execute->cmds->cmd_str,
//			"command not found", NULL);
//		return (127);
//	}
//}

int	execute_cmd(t_todo *all)
{
	int		filefd;
	char	**files;

	files = all->cur_cmds->input_files;
	if (all->cur_cmds->input_files)
	{
		while (*files)
		{
			filefd = open(*files, O_RDONLY, 0777);
			if (filefd == -1)
			{
				errorhandle(all, *files, "No such file or directory", "0");
				return (1);
			}
			if (!files + 1)
				dup2(filefd, STDIN_FILENO);
			files++;
		}
	}
	int		try;
	char	*bin_location;

	if (ft_strchr("./", all->cur_cmds->cmd_str[0]))
	{
		try = try_rel_abs_path(all);
		if (try)
			return (try);
	}
	if (is_builtin(all->cur_cmds->cmd_str))
		return (do_builtin(all->cur_cmds->cmd_str, all));
	bin_location = try_path(all);
	if (bin_location)
		return (start_process(all, bin_location));
	else
	{
		errorhandle(all, all->cur_cmds->cmd_str,
			"command not found", NULL);
		return (127);
	}
}

int	define_and_execute(t_todo *all)
{
	t_cmds	*cmds_cpy;
	int		ret;

	all->cur_cmds = all->to_execute->cmds;
	while (all->cur_cmds)
	{
		ret = execute_cmd(all);
		all->cur_cmds = all->cur_cmds->next;
	}
	return (ret);
}

int	execution(t_todo *all)
{
	int		ret;
	char	*ret_ascii;

	env_set_value(all, "?", "0");
	ret = define_and_execute(all);
	ret_ascii = ft_itoa(ret);
	env_set_value(all, "?", ret_ascii);
	free(ret_ascii);
	return (0);
}