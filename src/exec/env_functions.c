#include "../minishell.h"

static int add_env(char **env, const char **new_env)
{
	int		key_len;
	int		i;
	char 	*tmp;

	key_len = 0;
	i = 0;
	while ((*new_env)[key_len] && !ft_strchr("+=", (*new_env)[key_len]))
		key_len++;
	while (env[i])
	{
		if (!ft_strncmp(env[i], *new_env, key_len) && (env[i][key_len] == '=' || env[i][key_len] == '\0'))
		{
			if (!ft_strncmp(&(*new_env)[key_len], "+=", 2) && (*new_env)[key_len + 3])
			{
				tmp = env[i];
				env[i] = ft_strjoin(env[i], *new_env + key_len + 2);
				free(tmp);
			}
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

char *add_last_env(char const *env)
{
	char *new;
	int i;

	i = 0;
	while (env[i] && !ft_strchr("+=", env[i])) //lol+=wow
		i++;
	if (env[i] == '+')
	{
		new = ft_calloc(ft_strlen(env), sizeof(char));
		ft_strlcat(new, env, i + 1);
		ft_strlcat(new, env + i + 1, ft_strlen(env));
	}
	else
		new = ft_strdup(env);
	return (new);
}

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
		clone[i++] = add_last_env(new_env);
	clone[i] = NULL;
	return (clone);
}
