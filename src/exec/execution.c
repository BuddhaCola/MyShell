#include "../minishell.h"

int	start_process(t_todo *all, char *bin)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		set_redirections(all);
		execve(bin, all->cur_cmds->args, all->environments);
	}
	else
	{
		errno = 0;
		wait(&(all->exit_code));
		if (all->exit_code < 0)
			errorhandle(all, all->cur_cmds->cmd_str, NULL, NULL);
		free(bin);
	}
	return (all->exit_code);
}

int	execute_cmd_single(t_todo *all)
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
	{
		set_redirections(all);
		return (do_builtin(all->cur_cmds->cmd_str, all));
	}
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
	int		ret;

	if (all->cur_cmds->next)
		ret = execute_cmd_pipe(all);
	else
	{
		ret = execute_cmd_single(all);
		if (all->orig_stdout)
		{
			dup2(all->orig_stdout, STDOUT_FILENO);
			close(all->orig_stdout);
		}
		if (all->orig_stdin)
		{
			dup2(all->orig_stdin, STDIN_FILENO);
			close(all->orig_stdin);
		}
	}
	if (WIFSIGNALED(ret))
		ret = WTERMSIG(ret) + 128;
	else if (WIFEXITED(ret))
		ret = WEXITSTATUS(ret);
	return (ret);
}

int	execution(t_todo *all)
{
	int		ret;
	char	*ret_ascii;

	if (!all->to_execute->cmds)
		return (0);
	env_set_value(all, "?", "0");
	all->cur_cmds = all->to_execute->cmds;
	ret = define_and_execute(all);
	ret_ascii = ft_itoa(ret);
	env_set_value(all, "?", ret_ascii);
	free(ret_ascii);
	return (0);
}
