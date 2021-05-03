#include "../minishell.h"

static int	remove_env(char **env, char **new_env)
{
	int		key_len;
	int		i;

	key_len = 0;
	i = 0;
	while ((*new_env)[key_len])
		key_len++;
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
	return (0);
}

static int	ft_checkforbiddensymbols(char *str, int mode)
{
	while (*str)
	{
//		if (mode > 0 && *str != '=')
//			break;
		if (ft_isalnum(*str) || ((mode > 0 && ft_strchr("_=", *str)) || (mode < 0 && *str == '_')))
			str++;
		else
			return (1);
	}
	return (0);
}

static void insert_remove_env(t_todo *all, char *new_env, int mode)
{
	char	**clone;

	if (mode > 0)
		clone = clone_env(all->environments, new_env);
	else if (mode <= 0)
		clone = remove_env;
	i_want_to_be_freed(all->environments);
	all->environments = clone;
}

static int	validate_arg(char *newenv, int mode)
{
	if ((mode > 0 && ((newenv[0] == '=' || (ft_isdigit(newenv[0]))
					   || ft_checkforbiddensymbols(newenv, mode)))) ||
		(mode < 0 && ((ft_isdigit(newenv[0])) ||
					  ft_checkforbiddensymbols(newenv, mode))))
	{
		if (mode > 0)
			ft_putstr_fd("bash: export: `", 1);
		else
			ft_putstr_fd("bash: unset: `", 1);
		ft_putstr_fd(newenv, 1);
		ft_putstr_fd("': not a valid identifier\n", 1);
		return (0);
	}
	return (1);
}

int			set_unset_env(t_todo *all, int mode)
{
	int i;

	i = 1;
	while (all->to_execute->cmd->args[i])
	{
		if (validate_arg(all->to_execute->cmd->args[i++], mode))
			insert_remove_env(all, all->to_execute->cmd->args[i - 1], mode);
	}
	return (0);
}

static int	add_env(char **env, char **new_env)
{
	int		key_len;
	int		i;
	char 	*tmp;

	key_len = 0;
	i = 0;
	while ((*new_env)[key_len] && (*new_env)[key_len] != '=')
		key_len++;
	while (env[i])
	{
		if (!ft_strncmp(env[i], *new_env, key_len) && (env[i][key_len] == '=' || env[i][key_len] == '\0'))
		{
			if ((*new_env)[key_len] == '=')
			{
				PROBE
				tmp = env[i];
				env[i] = ft_strdup(*new_env);
				free(tmp);
				*new_env = NULL;
			}
			return (1);
		}
		i++;
	}
	return (0);
}

char	**clone_env(char **env, char *new_env)
{
	int		i;
	char	**clone;

	i = 0;
	while (env[i])
		i++;
	if (new_env && *new_env != '\0')
			add_env(env, &new_env);
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
