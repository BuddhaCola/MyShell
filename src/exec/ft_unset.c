#include "../minishell.h"

int ft_unset(t_todo *all)
{
	int i;

	if (all->cur_cmd_list->args[1])
	{
		i = 1;
		while (all->cur_cmd_list->args[i])
		{
			if (!validate_arg(all->to_execute->cmd->args[i], '-'))
			i++;
		}
	}
	return (0);
}