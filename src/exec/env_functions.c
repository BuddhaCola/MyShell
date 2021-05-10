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

static int	arg_insertion(char **oldenv, const char **new_env, int key_len)
{
	char	*tmp;

	if (!ft_strncmp(&(*new_env)[key_len], "+=", 2)
		&& (*new_env)[key_len + 2])
		appendarg(oldenv, new_env, key_len);
	if ((*new_env)[key_len] == '=')
	{
		tmp = *oldenv;
		*oldenv = ft_strdup(*new_env);
		free(tmp);
	}
	tmp = (char *)*new_env;
	free(tmp);
	*new_env = NULL;
	return (0);
}

static int	add_env(char **env, const char **new_env)
{
	int		key_len;
	int		i;

	key_len = 0;
	i = 0;
	while ((*new_env)[key_len] && !ft_strchr("+=", (*new_env)[key_len]))
		key_len++;
	while (env[i] && *new_env)
	{
		if (!ft_strncmp(env[i], *new_env, key_len)
			&& (env[i][key_len] == '=' || env[i][key_len] == '\0'))
			arg_insertion(&env[i], new_env, key_len);
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
