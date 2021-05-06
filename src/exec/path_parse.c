#include "../minishell.h"

static int is_builtin(char *path)
{
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
	{
		if (!(ft_strcmp(path, builtins[i++])))
		{
//			ft_putstr_fd("|is_builtin| It's builtin! 🎉\n", 1);
			return (1);
		}
	}
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

//char *try_absolute_path(t_todo *all,)

char *path_parse(t_todo *all, char *arg)
{
	char **path;
	char *bin;
	int i;

	bin = NULL;
	if ((ft_strchr("./", *arg)))
	{
		i = open(arg, O_RDONLY);
		if (i != -1)
		{
			close(i);
			return (arg);
		}
//		if ((bin = (check_here(".", &arg[2]))))
//		{
//			ft_putstr_fd("|found by relative path\n", 1);
//			return (bin);
//		}
		else
			return NULL;
	}
	if (arg[ft_strlen(arg) - 1] == '/')
	{
		ft_putstr_fd(arg, 1);
		ft_putstr_fd("is a directory!\n", 1);
		return (NULL);
	}
	if (!(ft_strcmp(arg, ".")))
	{
		ft_putstr_fd("bash: .: filename argument required\n", 1);
		return (NULL);
	}
	else if (!getenv("PATH"))
	{
		if ((bin = (check_here(".", arg))))
		{
			ft_putstr_fd("|samurai has no path. Found in current dir!\n", 1);
			return (bin);
		}
		else
			return NULL;
	}
	if (is_builtin(arg))
		return (arg);
	else
	{
		i = 0;
		path = ft_split(getenv("PATH"), ':');
		if (!path)
			ft_putstr_fd("malloc error 💩\n", 1);
		while (path[i])
		{
			bin = check_here(path[i], arg);
			if (bin)
			{
//				ft_putstr_fd("|found in PATH 👍\n", 1);
				i_want_to_be_freed(path);
				return (bin);
			}
			i++;
		}
	}
	i_want_to_be_freed(path);
	return (NULL);
}