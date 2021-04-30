#include "../minishell.h"

static int		ft_checkforbiddensymbols(char *str)
{
	while (*str)
	{
		if (ft_isdigit(*str) || *str == 32)
			str++;
		else if (*str == '-')

			return (1);
	}
	return (0);
}

int ft_exit(char **args, t_todo *all)
{
	unsigned char code;

	i = 0;
	return (code + ft_atoi(args[0]));
}