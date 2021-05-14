#include "../minishell.h"

char	*env_get_value(t_todo *all, char *key)
{
	char	**env_in_arr;
	char	*value;

	env_in_arr = env_search(all->environments, key);
	if (env_in_arr)
	{
		value = ft_strchr(*env_in_arr, '=');
		if (value && value + 1)
			value += 1;
	}
	else
		value = NULL;
	return (value);
}

char	**env_search(char **env, char *key)
{
	int	i;
	int	keylen;

	i = 0;
	keylen = 0;
	while (key[keylen] && key[keylen] != '=')
		keylen++;
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, keylen)
			&& (env[i][keylen] == '=' || env[i][keylen] == '\0'))
		{
			return (&env[i]);
		}
		i++;
	}
	return (NULL);
}
