#include "../minishell.h"
//
//char	*strjoin_filepath(char *path, char *bin, char* d_name)
//{
//	char	*found;
//	size_t			dst_size;
//
//	dst_size = ft_strlen(path) + ft_strlen(d_name) + 2;
//	found = ft_calloc(sizeof(char), dst_size);
//	ft_strlcat(found, path, dst_size);
//	ft_strlcat(found, "/", dst_size);
//	ft_strlcat(found, bin, dst_size);
//	return (found);
//}
//
//char	*check_here(char *path, char *bin)
//{
//	struct dirent	*current_file;
//	DIR				*directory;
//	char			*found;
//
//	directory = opendir(path);
//	if (directory == NULL)
//		return (NULL);
//	while (1)
//	{
//		current_file = readdir(directory);
//		if (current_file == NULL)
//			break ;
//		if (!(ft_strcmp(current_file->d_name, bin)))
//		{
//			closedir(directory);
//			return (strjoin_filepath(path, bin, current_file->d_name));
////			dst_size = ft_strlen(path) + ft_strlen(current_file->d_name) + 2;
////			found = ft_calloc(sizeof(char), dst_size);
////			ft_strlcat(found, path, dst_size);
////			ft_strlcat(found, "/", dst_size);
////			ft_strlcat(found, bin, dst_size);
////			closedir(directory);
////			return (found);
//		}
//	}
//	closedir(directory);
//	return (NULL);
//}
