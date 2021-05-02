#include "../minishell.h"

char	*ft_envpsearch(const char *haystack, const char *needle)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(needle);
	while (i < len && needle[i])
	{
		if (needle[i] == haystack[i])
			i++;
		else
			return (NULL);
	}
	if (haystack[i] == '=')
		return (ft_strdup(&haystack[++i]));
	return (NULL);
}

int	count_environments(t_todo *all)
{
	int	i;

	i = 0;
	all->env_count = 0;
	while (all->environments[i])
	{
		if (ft_strchr(all->environments[i], '='))
			all->env_count++;
		i++;
	}
	return (all->env_count);
}

static int add_env(char **env, const char **new_env)
{
	int		key_len;
	int		i;

	key_len = 0;
	i = 0;
	while ((*new_env)[key_len] && (*new_env)[key_len] != '=')
		key_len++;
	printf("|%s|key=|%.*s| keylen=%d\nnew_env[key_len]='%c'\n", *new_env, key_len, *new_env, key_len, (*new_env)[key_len]);
	while (env[i])
	{
		if (!ft_strncmp(env[i], *new_env, key_len) && (env[i][key_len] == '=' || env[i][key_len] == '\0'))
		{
			if ((*new_env)[key_len] == '=')
			{
				free(env[i]);
				env[i] = ft_strdup(*new_env);
			}
			*new_env = NULL;
			return (0);
		}
		i++;
	}
	return (1);
}

//int 	ft_unset(t_todo *all, char *env)
//{
//	int		i;
//	char 	**clone;
//
//	i = 0;
//	while (all->environments[i])
//		i++;
//	clone = malloc(sizeof(char *) * i);
//	if (clone == NULL)
//		return (NULL);
//	i = 0;
//	while (all->environments[i])
//	{
//		i++;
//	}
//	return (1);
//}

char	**clone_env(char **env, const char *new_env)
{
	int		i;
	char	**clone;

	i = 0;
	while (env[i])
		i++;
	if (new_env && *new_env != '\0')
		i += add_env(env, &new_env);
	clone = malloc(sizeof(char *) * i + 1);
	if (clone == NULL)
		return (NULL);
	i = 0;
	while (env[i])
	{
		clone[i] = ft_strdup(env[i]);
		i++;
	}
	if (new_env)
		clone[i++] = ft_strdup(new_env);
	clone[i] = NULL;
	return (clone);
}
