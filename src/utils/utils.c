#include "../minishell.h"

int	ft_checkforbiddensymbols_arg(char *str, int mode)
{
	if (mode == '+')
	{
		while (*str && *str != '=')
		{
			if (ft_isalnum(*str) || (ft_strchr("_=$", *str)
					|| !ft_strncmp(str, "+=", 2)))
				str++;
			else
				return (1);
		}
	}
	else if (mode == '-')
	{
		while (*str)
		{
			if (ft_isalnum(*str) || *str == '_')
				str++;
			else
				return (1);
		}
	}
	return (0);
}

void	appendarg(char **str, char **appendix, int key_len)
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
	free(*appendix);
	*appendix = NULL;
}

int	swapstr(char **str1, char **str2)
{
	char	*tmp;

	tmp = *str2;
	*str2 = *str1;
	*str1 = tmp;
	return (1);
}

int	ft_putchar(int c)
{
	return (write(STDOUT_FILENO, &c, 1));
}

void	i_want_to_be_freed(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
