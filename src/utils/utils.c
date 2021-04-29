#include "../minishell.h"

int ft_strcmp(char *str1, char *str2)
{
	int len1;
	int len2;

	if (!str1 || !str2)
		return (-1);

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	while (*str1 && *str2)
	{
		if (*str1++ - *str2++)
			return (*str1 - *str2);
	}
	return (*str1 - *str2);
}

int ft_putchar(int c)
{
	return (write(STDOUT_FILENO, &c, 1));
}

void i_want_to_be_freed(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

