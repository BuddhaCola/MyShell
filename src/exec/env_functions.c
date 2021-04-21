#include "../minishell.h"

int	count_environments(t_todo *all)
{
	all->env_count = 0;
	while (all->environments[all->env_count].name)
		all->env_count++;
	return (0);
}

int collect_env(t_todo *all, char **env)
{
	all->env_count = 0; //убрать в инициализацию
	char 	**tmp;

	all->env_count = 0;
	while (env[all->env_count])
		all->env_count++;
	all->environments = ft_calloc(all->env_count + 80, sizeof(t_env));
	if (all->environments == NULL)
		return (1);
	all->env_count = 0;
	while (env[all->env_count])
	{
		tmp = ft_split(env[all->env_count], '=');
		all->environments[all->env_count].name = tmp[0];
		all->environments[all->env_count].value = tmp[1];
		free(tmp);
		all->env_count++;
	}
	return (0);
}