#include "../minishell.h"
int ft_env(t_todo *all)
{
	while (all->environments->name)
	{
		printf("%s=%s\n", all->environments->name, all->environments->value);
		all->environments++;
	}
	return (0);
}