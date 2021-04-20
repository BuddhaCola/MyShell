#include "../minishell.h"

int sort_env(t_todo *all, int listlen)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(i < listlen)
	{
		j = 0;
		if (ft_strncmp(all->exec.environments[i].name, all->exec.environments[i + 1].name, ft_strlen(all->exec.environments[i].name))
		{
			i++;
		}
	}
	return (0);
}

void sprites()
{
t_sprite tmp;
int i;
int unsorted;
int left;

unsorted = 1;
left = all->spritecount - 1;
while (unsorted)
{
unsorted = 0;
i = 0;
while (i < left)
{
i++;
if (all->sprites[i - 1].dist < all->sprites[i].dist)
{
tmp = all->sprites[i];
all->sprites[i] = all->sprites[i - 1];
all->sprites[i - 1] =
tmp;
unsorted = 1;
}
}
left--;
}}

int collect_env(t_todo *all, char **env)
{
	int 	i;
	char 	**tmp;

	i = 0;
	while (env[i])
		i++;
	all->exec.environments = ft_calloc(i, sizeof(t_env));
	if (all->exec.environments == NULL)
		return (1);
	printf("i1 = %d\n", i);
	i = 0;
	while (env[i])
	{
		tmp = ft_split(env[i], '=');
		all->exec.environments[i].name = tmp[0];
		all->exec.environments[i].value = tmp[1];
		free(tmp);
		i++;
	}
	printf("i2 = %d\n", i);
	free(all->exec.environments);
	sort_env(all, i);
	return (0);
}