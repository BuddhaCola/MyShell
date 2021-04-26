#include "../minishell.h"

static int		ft_checkforbiddensymbols(char *str)
{
	while (*str != '=' && *str)
	{
		if (ft_isalnum(*str) || ft_strchr("_=", *str))
			str++;
		else
			return (1);
	}
	return (0);
}

static int sort_env(t_todo *all)
{
	t_env tmp;
	int	i;
	int	unsorted;
	int	remain;
	remain = count_environments(all);;

	while (unsorted)
	{
		unsorted = 0;
		i = 0;
		while (i < remain - 1)
		{
			i++;
			if (ft_strncmp(all->environments[i - 1].name, all->environments[i].name, ft_strlen(all->environments[i - 1].name)) > 0)
			{
				tmp = all->environments[i];
				all->environments[i] = all->environments[i - 1];
				all->environments[i - 1] =	tmp;
				unsorted = 1;
			}
		}
		remain--;
	}
	return (0);
}

int	print_env(t_todo *all)
{
	int i;

	i = 0;
	sort_env(all);
	while (all->environments[i].name)
	{
//		printf("|%d|", i);
//		fflush(stdout);
		ft_putstr_fd("declare -x " ,1);
		ft_putstr_fd(all->environments[i].name ,1);
		if (all->environments[i].value)
		{
			write(1, "=", 1);
			write(1, "\"", 1);
			ft_putstr_fd(all->environments[i].value, 1);
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		i++;
	}
	return (0);
}

int is_var_exist(t_todo *all, char **newenv)
{
	int i;

	i = 0;
	while (all->environments[i].name)
	{
		if (!(ft_strncmp(all->environments[i].name, newenv[0], ft_strlen(all->environments[i].name))))
			all->environments[i].value = ft_strdup(newenv[1]);
		i++;
	}
	return (0);
}

static int validate_arg(t_todo *all, char *newenv)
{
	char *underscore; // export _ ничего не записывает в экспорт
	if ((underscore = ft_strchr(newenv, '_')) && (!(ft_strchr("\0=", *underscore+1))))
		return (0);
	count_environments(all);
	if (newenv[0] == '=' || (ft_isdigit(newenv[0])) || ft_checkforbiddensymbols(newenv))  //ошибка
	{
		ft_putstr_fd("bash: export: `", 1);
		ft_putstr_fd(newenv, 1);
		ft_putstr_fd("': not a valid identifier\n", 1);
		return (1);
	}
	return (0);
}

int	set_env(t_todo *all, char *args)
{
	int		i;
	char 	**tmp;
	t_env	income_env;

	if (validate_arg(all, args))
		return (1);
	if (ft_strchr(args, '='))
	{
		tmp = ft_split(args, '=');
		income_env.name = ft_strdup(tmp[0]);
		income_env.value = ft_strdup(tmp[1]);
		free(tmp[0]);
		free(tmp[1]);
		free(tmp);
	}
	else
	{
		income_env.name = ft_strdup(args);
		income_env.value = NULL;
	}
	i = 0;
	while (i <= all->env_count)
	{
		if (!all->environments[i].name)
		{
			all->environments[i].name = ft_strdup(income_env.name);
			all->environments[i].value = ft_strdup(income_env.value);
			break;
		}
		if (!(ft_strncmp(all->environments[i].name, income_env.name, ft_strlen(all->environments[i].name))))
			if (all->environments[i].value)
			{
				all->environments[i].value = ft_strdup(income_env.value);
				break;
			}
		i++;
	}
	free(income_env.name);
	free(income_env.value);
	return (0);
}

int ft_export(t_todo *all, char *args)
{
//	args = malloc(sizeof(char *));
//	args[0] = "wow";
	if (!args)
		return (print_env(all));
	else
		set_env(all, args);
	return (0);
}