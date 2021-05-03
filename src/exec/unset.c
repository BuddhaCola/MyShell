#include "../minishell.h"

//char	**clone_env(char **env, const char *new_env)
//{
//	int		i;
//	char	**clone;
//
//	i = 0;
//	while (env[i])
//		i++;
//	if (new_env && *new_env != '\0')
//		i += add_env(env, &new_env);
//	clone = malloc(sizeof(char *) * i + 1);
//	if (clone == NULL)
//		return (NULL);
//	i = 0;
//	while (env[i])
//	{
//		clone[i] = ft_strdup(env[i]);
//		i++;
//	}
//	clone[i] = NULL;
//	return (clone);
//}

int ft_unset(t_todo *all)
{
	int i;

	if (all->cur_cmd_list->args[1])
	{
		i = 1;
		while (all->cur_cmd_list->args[i])
		{
			i++;
		}
	}
	return (0);
}