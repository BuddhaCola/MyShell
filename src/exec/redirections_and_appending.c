#include "../minishell.h"

static int	go_through_redirections(t_todo *all, char ***type, int mode)
{
	int	filefd;

	while (*type && **type)
	{
		filefd = open(**type, mode, 0644);
		if (filefd == -1)
		{
			errorhandle(all, "bash", "file open error", "-1");
			return (-1);
		}
		(*type)++;
	}
	return (filefd);
}

int	output_redirect(t_todo *all)
{
	char	**append;
	char	**output;
	int		filefd;

	all->orig_stdout = dup(STDOUT_FILENO);
	append = all->cur_cmds->append_files;
	output = all->cur_cmds->output_files;
	filefd = go_through_redirections(all, &append, APPEND_FILE);
	filefd = go_through_redirections(all, &output, OUTPUT_FILE);
	if (all->cur_cmds->file_type_flg == APPEND_FILE)
	{
		filefd = open(*(append - 1), APPEND_FILE, 0644);
		if (filefd == -1)
			return (-1);
	}
	else if (all->cur_cmds->file_type_flg == OUTPUT_FILE)
	{
		filefd = open(*(output - 1), OUTPUT_FILE, 0644);
		if (filefd == -1)
			return (-1);
	}
	if (dup2(filefd, 1) == -1)
		return (-1);
	close(filefd);
	return (all->orig_stdout);
}

int	input_redirect(t_todo *all)
{
	char	**files;
	int		filefd;

	files = all->cur_cmds->input_files;
	while (*files)
	{
		filefd = open(*files, O_RDONLY, 0644);
		if (filefd == -1)
		{
			errorhandle(all, *files, "No such file or directory", "0");
			return (-1);
		}
		if (!*(files + 1))
		{
			all->orig_stdin = dup(STDIN_FILENO);
			dup2(filefd, STDIN_FILENO);
		}
		files++;
	}
	return (all->orig_stdin);
}
