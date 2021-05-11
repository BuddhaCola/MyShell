#include "../minishell.h"

static char *check_here(char *path, char *bin)
{
	struct	dirent *lol;
	DIR		*directory;
	char 	*found;

	directory = opendir(path);
	if (directory == NULL)
		return (NULL);
	while (1)
	{
		lol = readdir(directory);
		if (lol == NULL)
			break ;
		if (!(ft_strcmp(lol->d_name, bin)))
		{
			size_t dst_size = ft_strlen(path) + ft_strlen(lol->d_name) + 2;
			found = ft_calloc(sizeof(char), dst_size);
			ft_strlcat(found, path, dst_size);
			ft_strlcat(found, "/", dst_size);
			ft_strlcat(found, bin, dst_size);
			closedir(directory);
			return (found);
		}
	}
	closedir(directory);
	return (NULL);
}

char	*try_path(t_todo *all)
{
	char	**path;
	char	**path_decomposed;
	int		i;
	char	*bin;

	bin = NULL;
	path = env_search(all->environments, "PATH");
	if (path)
	{
		i = 0;
		path_decomposed = ft_split(env_get_value(all, "PATH"), ':');
		if (!path_decomposed)
			return (NULL);
//			ft_putstr_fd("PATH splitting error 💩\n", 1);
		while (path_decomposed[i])
		{
//			printf("%s\n", all->to_execute->cmds->cmd_str);
			bin = check_here(path_decomposed[i], all->to_execute->cmds->cmd_str);
			if (bin)
				break;
			i++;
		}
		i_want_to_be_freed(path_decomposed);
	}
	return (bin);
}

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

int	define_and_execute(t_todo *all)
{
	int		try;
	char	*bin_location;

	if (ft_strchr("./", all->to_execute->cmds->cmd_str[0]))
	{
		try = try_rel_abs_path(all);
		if (try)
			return (try);
	}
	if (is_builtin(all->to_execute->cmds->cmd_str))
		return (do_builtin(all->to_execute->cmds->cmd_str, all));
	bin_location = try_path(all);
	if (bin_location)
		return (start_process(all, bin_location));
	else
	{
		errorhandle(all, all->to_execute->cmds->cmd_str, "command not found", "-1");
		return (127);
	}
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
