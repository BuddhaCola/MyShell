#include "../minishell.h"

void	env_set_value(t_todo *all, char *key, char *value)
{
	char	**val_in_arr;
	char	*ptr;
	char	*tmp;

	ptr = ft_strjoin(key, "=");
	tmp = ptr;
	ptr = ft_strjoin(ptr, value);
	free(tmp);
	val_in_arr = env_search(all->environments, key);
	if (!val_in_arr)
	{
		val_in_arr = all->environments;
		all->environments = clone_env(all->environments, ptr);
		free(val_in_arr);
	}
	else
	{
		tmp = *val_in_arr;
		*val_in_arr = ptr;
		free(tmp);
	}
}

void	increment_num_env(char **orig, char *key, int keylen)
{
	int		nu;
	char	*tmp;
	char	*itoad;
	char	*leftside;

	leftside = ft_strjoin(key, "=");
	if (!ft_strchr(*orig, '='))
	{
		tmp = *orig;
		*orig = ft_strdup(leftside);
		free(tmp);
	}
	nu = ft_atoi(ft_strchr(*orig, '=') + 1);
	itoad = ft_itoa(nu + 1);
	tmp = *orig;
	*orig = ft_strjoin(leftside, itoad);
	free(tmp);
	free(itoad);
	free(leftside);
}

void	create_leftside(t_todo *all, char *key, char *change, char mode)
{
	char	**clone;

	change = ft_strjoin(key, "=");
	clone = clone_env(all->environments, change);
	free(change);
	i_want_to_be_freed(all->environments);
	all->environments = clone;
	update_env(all, key, NULL, mode);
}

int	update_env(t_todo *all, char *key, char *change, char mode)
{
	char	**env_in_arr;
	char	**clone;

	env_in_arr = env_search(all->environments, key);
	if (mode == '+')
	{
		if (!env_in_arr)
			create_leftside(all, key, change, mode);
		else
			increment_num_env(env_in_arr, key, ft_strlen(key));
	}
	else if (mode == '?' && !env_in_arr)
	{
		clone = clone_env(all->environments, key);
		i_want_to_be_freed(all->environments);
		all->environments = clone;
	}
	return (0);
}