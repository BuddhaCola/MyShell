#include "../minishell.h"

void	eliminate_env(t_todo *all, int target_location)
{
	int		arrlen;
	char	*tmp;

	arrlen = 0;
	while (all->environments[arrlen])
		arrlen++;
	tmp = all->environments[target_location];
	all->environments[target_location] = all->environments[arrlen - 1];
	all->environments[arrlen - 1] = NULL;
	free(tmp);
}

void	search_and_destroy(t_todo *all, char *target)
{
	int	i;

	i = 0;
	while (all->environments[i])
	{
		if (!ft_strncmp(all->environments[i], target, ft_strlen(target))
			&& (all->environments[i][ft_strlen(target)] == '\0'
			||all->environments[i][ft_strlen(target)] == '='))
			eliminate_env(all, i);
		i++;
	}
}

int	ft_unset(t_todo *all)
{
	int	i;
	int	ret;

	ret = 0;
	if (all->cur_cmds->args[1])
	{
		i = 1;
		while (all->cur_cmds->args[i])
		{
			ret = validate_arg(all->cur_cmds->args[i], '-');
			if (ret == 0)
				search_and_destroy(all, all->cur_cmds->args[i]);
			i++;
		}
	}
	return (ret);
}
