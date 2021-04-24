#include "../minishell.h"

static int sort_env(t_todo *all)
{
	t_env tmp;
	int	i;
	int	unsorted;
	int	remain;
	remain = all->env_count;

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

static int	print_env(t_todo *all)
{
	int i;

	i = 0;
	sort_env(all);
	while (all->environments[i].name)
	{
		ft_putstr_fd("declare -x " ,1);
		ft_putstr_fd(all->environments[i].name ,1);
		write(1, "=", 1);
		write(1, "\"", 1);
		ft_putstr_fd(all->environments[i].value, 1);
		write(1, "\"", 1);
		write(1, "\n", 1);
		i++;
	}
	return (0);
}

int is_var_exist(t_todo *all, char **args)
{
	int i;
	int j;
	char **tmp;

	i = 0;
	return (0);
}

int	set_env(t_todo *all, char **args)
{
	int		i;
	char 	**tmp;
	t_env	income_env;

	i = 0;
	count_environments(all);
	if (ft_strchr(args[0], '='))
	{
		tmp = ft_split(tmp, '=');
		all->environments[all->env_count].name = tmp[0];
		all->environments[all->env_count].value = tmp[1];
		free(tmp);
	}
	else
		all->environments[all->env_count].name = args[0];
	return (0);
}

int ft_export(t_todo *all, char **args)
{
	char **lol;
	args = lol;
	args[0] = "foo=bar";
	if (!args)
		return (print_env(all));
	else
		set_env(all, args);
	return (0);
}