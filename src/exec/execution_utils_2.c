#include "../minishell.h"

static char	*strjoin_path(char *path, char *bin)
{
	size_t			dst_size;
	char			*found;

	dst_size = ft_strlen(path) + ft_strlen(bin) + 2;
	found = ft_calloc(sizeof(char), dst_size);
	ft_strlcat(found, path, dst_size);
	ft_strlcat(found, "/", dst_size);
	ft_strlcat(found, bin, dst_size);
	return (found);
}

static char	*check_here(char *path, char *bin)
{
	struct dirent	*curr_dir;
	DIR				*directory;
	char			*found;

	directory = opendir(path);
	if (directory == NULL)
		return (NULL);
	while (1)
	{
		curr_dir = readdir(directory);
		if (curr_dir == NULL)
			break ;
		if (!(ft_strcmp(curr_dir->d_name, bin)))
		{
			closedir(directory);
			return (strjoin_path(path, bin));
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
		while (path_decomposed[i])
		{
			bin = check_here
				(path_decomposed[i], all->to_execute->cmds->cmd_str);
			if (bin)
				break ;
			i++;
		}
		i_want_to_be_freed(path_decomposed);
	}
	return (bin);
}
