#include "../minishell.h"

static int is_builtin(char *path)
{
	if (!path)
		return (0);
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
		if (!ft_strcmp(builtins[i++], path))
			return (1);
	return (0);
}

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
		return (ft_exit(all->to_execute->cmds->args, all));
	return (0);
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

int	execution(t_todo *all)
{
	int		fd;
	char	*bin_location;

	if (ft_strchr("./", all->to_execute->cmds->cmd_str[0]))
	{
		fd = open(all->to_execute->cmds->cmd_str, O_RDONLY);
		if (fd != -1)
		{
			bin_location = ft_strdup(all->to_execute->cmds->cmd_str);
			close(fd);
			return (start_process(all, bin_location));
		}
	}
	if (is_builtin(all->to_execute->cmds->cmd_str))
		return (do_builtin(all->to_execute->cmds->cmd_str, all));
	bin_location = try_path(all);
	if (bin_location)
		return (start_process(all, bin_location));
	else
	{
		ft_putstr_fd("bash: ", 1);
		ft_putstr_fd(all->to_execute->cmds->cmd_str, 1);
		ft_putstr_fd(": command not found 😑\n", 1);
		return (127);
	}
}

int	exec_bin(t_todo *all)
{
	int		ret;
	char	*ret_ascii;

	env_set_value(all, "?", "0");
	ret = execution(all);
	ret_ascii = ft_itoa(ret);
	env_set_value(all, "?", ret_ascii);
	free(ret_ascii);
	return (0);
}
