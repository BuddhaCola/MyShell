#include "../minishell.h"
int	ft_env(t_todo *all)
{
	int	i;

	i = 0;
	if (all->cur_cmds->args[1] != NULL)
		return ((int)write(1,
				"env: env without any options and any arguments\n", 47));
	if (!all->environments)
		return ((int)write(1, "env: env is a NULL pointer\n", 8));
	while (all->environments[i] != NULL)
	{
		if (ft_strchr(all->environments[i], '='))
			if (*all->environments[i] != '?')
				ft_putendl_fd(all->environments[i], 1);
		i++;
	}
	return (0);
}
