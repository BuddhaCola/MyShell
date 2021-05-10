#include "../minishell.h"



int	ft_checkforbiddensymbols_arg(char *str, int mode)
{
	if (mode == '+')
		while (*str && *str != '=')
		{
			if (ft_isalnum(*str) || (ft_strchr("_=$", *str) || !ft_strncmp(str, "+=", 2)))
				str++;
			else
				return (1);
		}
	else if (mode == '-')
		while (*str)
		{
			if (ft_isalnum(*str) || *str == '_')
				str++;
			else
				return (1);
		}
	return (0);
}

void	appendarg(char **str, const char **appendix, int key_len)
{
	char	*tmp;

	if (!ft_strchr(*str, '='))
	{
		tmp = *str;
		*str = ft_strjoin(*str, "=");
		free(tmp);
	}
	tmp = *str;
	*str = ft_strjoin(*str, *appendix + key_len + 2);
	free(tmp);
}

int	swapstr(char **str1, char **str2)
{
	char	*tmp;

	tmp = *str2;
	*str2 = *str1;
	*str1 = tmp;
	return (1);
}

int ft_strcmp(char *str1, char *str2)
{
	int	bigger;

	if (!str1 || !str2)
		return -1;
	if (ft_strlen(str1) >= ft_strlen(str2))
		bigger = ft_strlen(str1);
	else
		bigger = ft_strlen(str2);
	return (ft_strncmp(str1, str2, bigger));
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
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

