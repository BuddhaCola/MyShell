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

int ft_export(t_todo *all)
{
	if (!all->to_execute->cmd->args[1])
		return (print_env(all));
	else
		set_unset_env(all, 1);
	return (1);
}