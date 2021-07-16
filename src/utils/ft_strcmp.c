#include "../minishell.h"

int	ft_strcmp(char *str1, char *str2)
{
	int	bigger;

	if (!str1 || !str2)
		return (-1);
	if (ft_strlen(str1) >= ft_strlen(str2))
		bigger = ft_strlen(str1);
	else
		bigger = ft_strlen(str2);
	return (ft_strncmp(str1, str2, bigger));
}
