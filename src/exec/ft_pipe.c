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

int	ft_pipe(t_todo *all)
{
	int		pipeline[2];
	pid_t	pid;
	int		fd_in;
	int i = 0;
	int count_cmd = 0;
	int	exitcode;
	fd_in = -1;
	char	*to_execute;

	while(all->cur_cmds)
	{
		count_cmd++;
		pipe(pipeline);

		pid = fork();
		if (pid == -1)
			exit (-1);
		else if (pid == 0)
		{
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
			if (is_builtin(all->cur_cmds->cmd_str))
			{
//				(do_builtin(all->cur_cmds->cmd_str, all));
				exit((do_builtin(all->cur_cmds->cmd_str, all)));
			}
			else
				to_execute = find_location_pipe(all);
			fprintf(stderr, "to_execute: %s\n", to_execute);
//			execvp(to_execute, all->cur_cmds->args);
			execve(to_execute, all->cur_cmds->args, all->environments);
			exit(EXIT_FAILURE);
		}
		else
		{
			close(pipeline[1]);
			close(fd_in);
			fd_in = dup(pipeline[0]);
			close(pipeline[0]);
			all->cur_cmds = all->cur_cmds->next;
		}
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