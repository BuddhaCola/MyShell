#include "../minishell.h"

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
	else if (!(ft_strcmp(path, "get_value")))
		env_get_value(all, all->cur_cmd_list->args[1]);
	else
		return (0);
	ft_putstr_fd(" under construction! 🚧\n", 1);
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
//			printf("%s\n", all->to_execute->cmd->cmd_str);
			bin = check_here(path_decomposed[i], all->to_execute->cmd->cmd_str);
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
	{
		all->exec.err = execve(bin, all->to_execute->cmd->args, all->environments);
	}
	else
		wait(&pid);
	return (0);
}

int	exec_bin(t_todo *all)
{
	int		ret;
	char	*bin_location;

	if (ft_strchr("./", all->to_execute->cmd->cmd_str[0]))
	{
		ret = open(all->to_execute->cmd->cmd_str, O_RDONLY);
		if (ret != -1)
		{
			close(ret);
			return (start_process(all, all->to_execute->cmd->cmd_str));
		}
	}
	if (do_builtin(all->to_execute->cmd->cmd_str, all) != 0)
		return (all->exit_code);
	bin_location = try_path(all);
	if (bin_location)
		return (start_process(all, bin_location));
	else
	{
		ft_putstr_fd("bash: ", 1);
		ft_putstr_fd(all->to_execute->cmd->cmd_str, 1);
		ft_putstr_fd(": command not found 😑\n", 1);
		return (0);
	}
	free(all->to_execute->cmd->cmd_str);
	return (1);
}
