#include "../minishell.h"
int ft_env(t_todo *all)
{
	while (*all->exec.env)
	{
		printf("%s\n", *all->exec.env);
		all->exec.env++;
	}
	return (0);
}