#include "../minishell.h"

void	env_insetion(t_todo *all, char *insertion, char *key)
{
	char	**val_in_arr;
	char	**clone;
	char	*tmp;

	val_in_arr = env_search(all->environments, key);
	if (!val_in_arr)
	{
		clone = clone_env(all->environments, insertion);
		i_want_to_be_freed(all->environments);
		all->environments = clone;
		free(insertion);
	}
	else
	{
		tmp = *val_in_arr;
		*val_in_arr = insertion;
		free(tmp);
	}
}

void	env_set_value(t_todo *all, char *key, char *value)
{
	char	*insertion;
	char	*tmp;

	if (value)
	{
		insertion = ft_strjoin(key, "=");
		tmp = insertion;
		insertion = ft_strjoin(insertion, value);
		free(tmp);
	}
	else
		insertion = ft_strdup(key);
	env_insetion(all, insertion, key);
}

void	increment_num_env(char **orig, char *key)
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
	env_update(all, key, NULL, mode);
}

int	env_update(t_todo *all, char *key, char *change, char mode)
{
	char	**env_in_arr;
	char	**clone;

	env_in_arr = env_search(all->environments, key);
	if (mode == '+')
	{
		if (!env_in_arr)
			create_leftside(all, key, change, mode);
		else
			increment_num_env(env_in_arr, key);
	}
	else if (mode == '?' && !env_in_arr)
	{
		clone = clone_env(all->environments, key);
		i_want_to_be_freed(all->environments);
		all->environments = clone;
	}
	return (0);
}
