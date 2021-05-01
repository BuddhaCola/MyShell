#include "../minishell.h"

//static int		ft_checkforbiddensymbols(char *str)
//{
//	while (*str != '=' && *str)
//	{
//		if (ft_isalnum(*str) || ft_strchr("_=", *str))
//			str++;
//		else
//			return (1);
//	}
//	return (0);
//}
//
//
//int is_var_exist(t_todo *all, char **newenv)
//{
//	int i;
//
//	i = 0;
//	while (all->environments[i].name)
//	{
//		if (!(ft_strncmp(all->environments[i].name, newenv[0], ft_strlen(all->environments[i].name))))
//			all->environments[i].value = ft_strdup(newenv[1]);
//		i++;
//	}
//	return (0);
//}
//
//static int validate_arg(t_todo *all, char *newenv)
//{
//	char *underscore; // export _ ничего не записывает в экспорт
//	if ((underscore = ft_strchr(newenv, '_')) && (!(ft_strchr("\0=", *underscore+1))))
//		return (0);
//	count_environments(all);
//	if (newenv[0] == '=' || (ft_isdigit(newenv[0])) || ft_checkforbiddensymbols(newenv))  //ошибка
//	{
//		ft_putstr_fd("bash: export: `", 1);
//		ft_putstr_fd(newenv, 1);
//		ft_putstr_fd("': not a valid identifier\n", 1);
//		return (1);
//	}
//	return (0);
//}
//
//int	set_env(t_todo *all, char *args)
//{
//	int		i;
//	char 	**tmp;
//	t_env	income_env;
//
//	if (validate_arg(all, args))
//		return (1);
//	if (ft_strchr(args, '='))
//	{
//		tmp = ft_split(args, '=');
//		income_env.name = ft_strdup(tmp[0]);
//		income_env.value = ft_strdup(tmp[1]);
//		free(tmp[0]);
//		free(tmp[1]);
//		free(tmp);
//	}
//	else
//	{
//		income_env.name = ft_strdup(args);
//		income_env.value = NULL;
//	}
//	i = 0;
//	while (i <= all->env_count)
//	{
//		if (!all->environments[i].name)
//		{
//			all->environments[i].name = ft_strdup(income_env.name);
//			all->environments[i].value = ft_strdup(income_env.value);
//			break;
//		}
//		if (!(ft_strncmp(all->environments[i].name, income_env.name, ft_strlen(all->environments[i].name))))
//			if (all->environments[i].value)
//			{
//				all->environments[i].value = ft_strdup(income_env.value);
//				break;
//			}
//		i++;
//	}
//	free(income_env.name);
//	free(income_env.value);
//	return (0);
//}

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
	clone = clone_env(all->environments);
	clone = sort_env(clone);
	while (clone[i])
		print_one(clone[i++]);
	i_want_to_be_freed(clone);
	return (1);
}

int ft_export(t_todo *all)
{
	if (!all->simple_command_list->cmd->args[1])
		return (print_env(all));
//	else
//		set_env(all);
	return (1);
}