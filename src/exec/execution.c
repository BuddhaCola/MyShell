#include "../minishell.h"

int	start_process(t_todo *all, char *bin)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (all->cur_cmds->input_files)
		{
			all->orig_stdin = input_redirect(all);
			if (all->orig_stdin == -1)
				return (1);
		}
		if (all->cur_cmds->output_files || all->cur_cmds->append_files)
			all->orig_stdout = output_redirect(all);
		execve(bin, all->to_execute->cmds->args, all->environments);
	}
	else
	{
		errno = 0;
		wait(&(all->exit_code));
		all->exit_code /= 255;
		if (all->exit_code < 0)
			errorhandle(all, all->to_execute->cmds->cmd_str, NULL, NULL);
		free(bin);
		if (all->cur_cmds->input_files)
			dup2(all->orig_stdin, STDIN_FILENO);
		if (all->cur_cmds->output_files || all->cur_cmds->append_files)
			dup2(all->orig_stdout, STDOUT_FILENO);
	}
	return (all->exit_code);
}
//
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

//void	close_pipes(t_todo *all)
//{
//	t_cmds *cmds_cpy;
//
//	cmds_cpy = all->to_execute->cmds;
//	while (cmds_cpy)
//	{
//		close(cmds_cpy->pipeline_in);
//		cmds_cpy = cmds_cpy->next;
//	}
//}

int	define_and_execute(t_todo *all)
{
	int		ret;

	all->cur_cmds = all->to_execute->cmds;
	if (all->cur_cmds->next)
	{
		ret = ft_pipe(all);
//		close_pipes(all);
	}
	else
		ret = execute_cmd(all);
//	if (WIFSIGNALED(ret))
//		ret = WTERMSIG(ret) + 128;
//	else if (WIFEXITED(ret))
//		ret = WEXITSTATUS(ret);
	return (ret);
}

//int	define_and_execute(t_todo *all)
//{
//	int		ret;
//
//	all->cur_cmds = all->to_execute->cmds;
//	while(all->cur_cmds)
//	{
//		ret = execute_cmd(all);
//		all->cur_cmds = all->cur_cmds->next;
//	}
//	return (ret);
//}

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
