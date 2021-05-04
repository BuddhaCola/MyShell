#include "../minishell.h"

char	**env_search(char **env, char *key)
{
	int	i;
	int	keylen;

	i = 0;
	keylen = 0;
	while (key[keylen] && key[keylen] != '=')
		keylen++;
	while(env[i])
	{
		if (!ft_strncmp(env[i], key, keylen)
			&& (env[i][keylen] == '=' || env[i][keylen] == '\0'))
		{
			return (&env[i]);
		}
		i++;
	}
	return NULL;
}

static int		ft_checkforbiddensymbols_shlvl(char *str)
{
	while (*str)
	{
		if (ft_strchr("0123456789-+ \0", *str))
			str++;
		else
			return (1);
	}
	return (0);
}

//int	increment_num_env(char **orig, char *key, int keylen)
//{
//	int		nu;
//	char	*tmp;
//
////	if (ft_checkforbiddensymbols_shlvl((ft_strchr(*orig, '=') + 1)))
////	{
////		PROBE
////		tmp = *orig;
////		*orig = ft_strdup("SHLVL=0");
////		free(tmp);
////	}
////
////	if (!ft_isdigit(*(ft_strchr(*orig, '=') + 1))
////		|| ft_atoi(ft_strnstr(*orig, "=", ft_strlen(*orig)) + 1) < 0)
////	{
////		key = ft_strjoin(key, "=");
////		tmp = key;
////		*orig = ft_strdup(key);
////		free(tmp);
////		tmp = *orig;
////	}
//	nu = ft_atoi(ft_strchr(*orig, '=') + 1);
////	if (nu >= 999 || ft_strlen(ft_strchr(*orig, '=') + 1) > 3)
////	{
////		safe_strdup(orig, "SHLVL=\"\"");
////		return (1);
////	}
////	if (tmp)
////		free(tmp);
//	tmp = ft_itoa(nu + 1);
//	key = ft_strjoin(key, tmp);
//	free (tmp);
//	tmp = key;
////	safe_strjoin(&key, tmp);
////	safe_strdup(orig, key);
//	return (1);
//}

char	*safe_strjoin(char **orig, char *appendix)
{
	char	*tmp;

	tmp = *orig;
	*orig = ft_strjoin(*orig, appendix);
	free(tmp);
	return (*orig);
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

int	update_env(t_todo *all, char *key, char *change, char mode)
{
	int		i;
	char	**env_in_arr;
	char	**clone;

	env_in_arr = env_search(all->environments, key);
	if (mode == '+')
	{
		if (!env_in_arr)
		{
			change = ft_strjoin(key, "=");
			clone = clone_env(all->environments, change);
			free(change);
			i_want_to_be_freed(all->environments);
			all->environments = clone;
			update_env(all, key, NULL, mode);
		}
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
