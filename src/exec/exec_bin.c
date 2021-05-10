#include "../minishell.h"

static int do_builtin(char *path, t_todo *all)
{
	if (!(ft_strcmp(path, "echo")))
		return (ft_echo(all));
	else if (!(ft_strcmp(path, "cd")))
		return (ft_cd(all));
	else if (!(ft_strcmp(path, "pwd")))
		return (ft_pwd());
	else if (!(ft_strcmp(path, "export")))
		return (ft_export(all));
	else if (!(ft_strcmp(path, "unset")))
		return (ft_unset(all));
	else if (!(ft_strcmp(path, "env")))
		return (ft_env(all));
	else if (!(ft_strcmp(path, "exit")))
		ft_exit(all->to_execute->cmds->args, all);
	else if (!(ft_strcmp(path, "get_value")))
		env_get_value(all, all->to_execute->cmds->args[1]);
	return (1);
}

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
	char	*status;

	pid = fork();
	if (!pid)
		all->exec.err = execve(bin, all->to_execute->cmds->args, all->environments);
	else
	{
		errno = 0;
		wait(&(all->exit_code));
		status = ft_itoa(all->exit_code / 255);
		env_set_value(all, "?", status);
		free(status);
		if (errno)
			ft_putstr_fd(strerror(errno), 1);
		free (bin);
	}
	return (0);
}

int	exec_bin(t_todo *all)
{
	int		try_open;
	char	*bin_location;

	if (ft_strchr("./", all->to_execute->cmds->cmd_str[0]))
	{
		try_open = open(all->to_execute->cmds->cmd_str, O_RDONLY);
		if (try_open != -1)
		{
			close(try_open);
			return (start_process(all, all->to_execute->cmds->cmd_str));
		}
	}
	if (do_builtin(all->to_execute->cmds->cmd_str, all) == 0)
		return (all->exit_code);
	bin_location = try_path(all);
	if (bin_location)
		return (start_process(all, bin_location));
	else
	{
		ft_putstr_fd("bash: ", 1);
		ft_putstr_fd(all->to_execute->cmds->cmd_str, 1);
		ft_putstr_fd(": command not found 😑\n", 1);
		return (0);
	}
	free(all->to_execute->cmds->cmd_str);
	return (1);
}
