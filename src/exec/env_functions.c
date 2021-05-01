#include "../minishell.h"

char	*ft_envpsearch(const char *haystack, const char *needle)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(needle);

	while(i < len && needle[i])
	{
		if (needle[i] == haystack[i])
			i++;
		else
			return (NULL);
	}
	if (haystack[i] == '=')
		return (ft_strdup(&haystack[++i]));
	return (NULL);
}

int	count_environments(t_todo *all)
{
	int	i;

	i = 0;
	all->env_count = 0;
	while (all->environments[i])
	{
		if (ft_strchr(all->environments[i], '='))
			all->env_count++;
		i++;
	}
	return (all->env_count);
}

char **clone_env(char **env)
{
	int i;
	char **clone;

	i = 0;
	while (env[i])
		i++;
	clone = malloc(sizeof(char *) * i + 1);
	if (clone == NULL)
		return (NULL);
	i = 0;
	while (env[i])
	{
		clone[i] = ft_strdup(env[i]);
		i++;
	}
	clone[i] = NULL;
	return (clone);
}

//int collect_env(t_todo *all, char **env)
//{
//	all->env_count = 0; //убрать в инициализацию
//	char 	**tmp;
//
//	all->env_count = 0;
//	while (env[all->env_count])
//		all->env_count++;
//	all->environments = ft_calloc(all->env_count + 100, sizeof(t_env));
//	if (all->environments == NULL)
//		return (1);
//	all->env_count = 0;
//	while (env[all->env_count])
//	{
//		tmp = ft_split(env[all->env_count], '=');
//		all->environments[all->env_count].name = tmp[0];
//		all->environments[all->env_count].value = tmp[1];
//		free(tmp);
//		all->env_count++;
//	}