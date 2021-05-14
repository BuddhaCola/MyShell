#include "../minishell.h"

char	*find_location_pipe(t_todo *all)
{
	char	*bin_location;

	if (ft_strchr("./", all->cur_cmds->cmd_str[0]))
	{
		bin_location = try_open(all);
		if (bin_location)
			return (bin_location);
		else if (ft_strchr("./", all->cur_cmds->cmd_str
				[ft_strlen(all->cur_cmds->cmd_str) - 1]))
		{
			errorhandle
					(all, all->cur_cmds->cmd_str, "is a directory", "126");
			exit (126);
		}
	}
	bin_location = try_path(all);
	if (bin_location)
		return (bin_location);
	else
	{
		errorhandle(all, all->cur_cmds->cmd_str,
			"command not found", "127");
		exit (127);
	}
}

void	child_process(t_todo *all, int fd_in, int pipeline[2])
{
	char	*to_execute;

	if (fd_in > 0)
	{
		dup2(fd_in, 0);
		close(fd_in);
	}
	if (all->cur_cmds->next != NULL)
		dup2(pipeline[1], 1);
	close(pipeline[0]);
	close(pipeline[1]);
	set_redirections(all);
	if (is_builtin(all->cur_cmds->cmd_str))
		exit(do_builtin(all->cur_cmds->cmd_str, all));
	to_execute = find_location_pipe(all);
	execve(to_execute, all->cur_cmds->args, all->environments);
	exit(EXIT_FAILURE);
}

void	parent_process(t_todo *all, int *fd_in, int pipeline[2])
{
	close(pipeline[1]);
	close(*fd_in);
	*fd_in = dup(pipeline[0]);
	close(pipeline[0]);
	all->cur_cmds = all->cur_cmds->next;
}

int	pipe_loop(t_todo *all)
{
	int		pipeline[2];
	pid_t	pid;
	int		fd_in;
	int		count_cmd;

	count_cmd = 0;
	while (all->cur_cmds)
	{
		count_cmd++;
		pipe(pipeline);
		pid = fork();
		if (pid == -1)
			exit (-1);
		else if (pid == 0)
			child_process(all, fd_in, pipeline);
		else
			parent_process(all, &fd_in, pipeline);
	}
	close(fd_in);
	return (count_cmd);
}

int	execute_cmd_pipe(t_todo *all)
{
	int		i;
	int		count_cmd;
	int		ret;

	i = 0;
	count_cmd = pipe_loop(all);
	while (i < count_cmd)
	{
		wait(&ret);
		i++;
	}
	if (WIFSIGNALED(ret))
		all->exit_code = WTERMSIG(ret) + 128;
	if (WIFEXITED(ret))
		all->exit_code = WEXITSTATUS(ret);
	all->exit_code = all->exit_code & 0377;
	return (all->exit_code);
}
