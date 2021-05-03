#include "../minishell.h"

char	**sort_env(char **env)
{
	int		i;
	int		unsorted;
	int		remain;
	char	*tmp;

	remain = 0;
	while (env[remain])
		remain++;
	unsorted = 1;
	while (unsorted)
	{
		unsorted = 0;
		i = 0;
		while (i < remain - 1)
		{
			i++;
			if (ft_strncmp(env[i - 1], env[i], ft_strlen(env[i - 1])) > 0)
			{
				tmp = env[i];
				env[i] = env[i - 1];
				env[i - 1] = tmp;
				unsorted = 1;
			}
		}
		remain--;
	}
	return (env);
}

void print_one(char *clone)
{
	if (ft_strncmp(clone, "_=", 2))
	{
		ft_putstr_fd("declare -x ", 1);
		{
			while (*clone && *clone != '=')
				write(1, clone++, 1);
			if (*clone == '=') {
				ft_putstr_fd("=\"", 1);
				while (*(++clone))
					write(1, clone, 1);
				ft_putstr_fd("\"", 1);
			}
		}
		write(1, "\n", 1);
	}
}

int	print_env(t_todo *all)
{
	int		i;
	char	**clone;

	i = 0;
	clone = clone_env(all->environments, NULL);
	clone = sort_env(clone);
	while (clone[i])
		print_one(clone[i++]);
	i_want_to_be_freed(clone);
	return (1);
}

static int	ft_checkforbiddensymbols(char *str)
{
	while (*str && *str != '=')
	{
		if (ft_isalnum(*str) || ft_strchr("_=", *str) || !ft_strncmp(str, "+=", 2))
			str++;
		else
			return (1);
	}
	return (0);
}

static int	validate_arg(char *newenv)
{
	if (ft_strchr("+=$", newenv[0]) || (ft_isdigit(newenv[0])) || ft_checkforbiddensymbols(newenv))  //ошибка
	{
		ft_putstr_fd("bash: export: `", 1);
		ft_putstr_fd(newenv, 1);
		ft_putstr_fd("': not a valid identifier\n", 1);
		return (1);
	}
	return (0);
}

//static void new_env(t_todo *all, char *new_env)
//{
//	char	**clone;
//
//	clone = clone_env(all->environments, new_env);
//	i_want_to_be_freed(all->environments);
//	all->environments = clone;
//}

//int			set_env(t_todo *all)
//{
//	int i;
//
//	i = 1;
//	while (all->to_execute->cmd->args[i])
//	{
//		if (!validate_arg(all->to_execute->cmd->args[i++]))
//			new_env(all, all->to_execute->cmd->args[i - 1]);
//	}
//	return (0);
//}

int ft_export(t_todo *all)
{
	int		i;
	char	**clone;

	if (!all->to_execute->cmd->args[1])
		return (print_env(all));
	else
	{
		i = 1;
		while (all->to_execute->cmd->args[i])
		{
			if (!validate_arg(all->to_execute->cmd->args[i++]))
			{
				clone = clone_env(all->environments,all->to_execute->cmd->args[i - 1]);
				i_want_to_be_freed(all->environments);
				all->environments = clone;
			}
		}
	}
	return (1);
}