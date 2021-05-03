#include "../minishell.h"

int ft_unset(t_todo *all)
{
	if (all->to_execute->cmd->args[1])
		set_unset_env(all, -1);
	return (1);
}