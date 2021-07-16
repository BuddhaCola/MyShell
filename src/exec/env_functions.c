#include "../minishell.h"

int	validate_arg(char *newenv, char mode)
{
	if (ft_strchr("+=$", newenv[0]) || (ft_isdigit(newenv[0]))
		|| ft_checkforbiddensymbols_arg(newenv, mode))
	{
		if (mode == '+')
			ft_putstr_fd("bash: export: `", 1);
		else if (mode == '-')
			ft_putstr_fd("bash: unset: `", 1);
		ft_putstr_fd(newenv, 1);
		ft_putstr_fd("': not a valid identifier\n", 1);
		return (1);
	}
	return (0);
}

static int	arg_change(char **oldenv, char **new_env, int key_len)
{
	char	*tmp;

	if (!ft_strncmp(&(*new_env)[key_len], "+=", 2)
		&& (*new_env)[key_len + 2])
		appendarg(oldenv, new_env, key_len);
	else if ((*new_env)[key_len] == '=')
	{
		tmp = *oldenv;
		*oldenv = ft_strdup(*new_env);
		free(tmp);
		free(*new_env);
		*new_env = NULL;
	}
	return (0);
}

static int	add_env(char **env, char **new_env)
{
	int		key_len;
	int		i;

	key_len = 0;
	i = 0;
	while ((*new_env)[key_len] && !ft_strchr("+=", (*new_env)[key_len]))
		key_len++;
	while (env[i])
	{
		if (!ft_strncmp(env[i], *new_env, key_len))
		{
			if ((*new_env)[key_len] == '=' || (*new_env)[key_len] == '+')
				arg_change(&env[i], new_env, key_len);
			else
			{
				free(*new_env);
				*new_env = NULL;
			}
			return (0);
		}
		i++;
	}
	return (1);
}

char	*add_last_env(char const *env)
{
	char	*new;
	int		i;

	i = 0;
	while (env[i] && !ft_strchr("+=", env[i]))
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

char	**clone_env(char **env, const char *arg)
{
	int		i;
	char	**clone;
	char	*new_env;

	new_env = ft_strdup(arg);
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
	free(new_env);
	clone[i] = NULL;
	return (clone);
}
