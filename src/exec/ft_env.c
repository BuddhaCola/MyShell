#include "../minishell.h"
int ft_env(t_todo *all)
{
	int i;

	i = 0;
	if (all->to_execute->cmd->args[1] != NULL)
		return ((int)write(1, "env: env without any options and any arguments\n", 47));
	if (!all->environments)
		return ((int)write(1, "env: env is a NULL pointer\n", 8));
	while (all->environments[i] != NULL)
	{
		if (ft_strchr(all->environments[i], '='))
		{
			ft_putstr_fd(all->environments[i], 1);
			ft_putstr_fd("\n", 1);
		}
		i++;
	}
	return (1);
}