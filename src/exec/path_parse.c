#include "../minishell.h"

char *check_here(char *path, char *bin)
{
	struct	dirent *lol;
	DIR		*directory;
	char 	*found;

	directory = opendir(path);
	while ((lol = readdir(directory)))
		if (!(ft_strncmp(lol->d_name, bin, ft_strlen(lol->d_name))))
		{
			closedir(directory);
			found = malloc(sizeof(char) * (ft_strlen(path) + ft_strlen(lol->d_name) + 2));
			ft_strlcpy(found, path, ft_strlen(path) + 1);
			ft_strlcat(found, "/", ft_strlen(found) + 2);
			ft_strlcat(found, bin, ft_strlen(found) + ft_strlen(bin) + 1);
			return (found);
		}
	closedir(directory);
	return (NULL);
}

char *path_parse(t_todo *all, char *arg)
{
	char **path;
	char *bin;
	int i;

	i = -1;
	path = ft_split(get_env_value(all, "PATH"), ':');
	while (path[++i])
		if ((bin = check_here(path[i], arg)))
			return (bin);
	i_want_to_be_freed(path);
	return (NULL);
}