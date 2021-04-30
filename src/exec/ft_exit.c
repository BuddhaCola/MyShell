#include "../minishell.h"

static int		ft_checkforbiddensymbols(char *str)
{
	while (*str)
	{
		if (ft_isdigit(*str) || *str == 32 || ft_strchr("-+", *str))
			str++;
		else
			return (1);
	}
	return (0);
}

int ft_exit(char **args, t_todo *all)
{
	unsigned char	exit_code;
	int 			code;

	if (args)
	{
		if (ft_checkforbiddensymbols(args[1]))
		{
			ft_putstr_fd("exit: numeric argument required 😠\n", 1);
			exit (-1);
		}
		else
			code = ft_atoi(args[1]);
		if (args[2])
		{
			ft_putstr_fd("exit: too many arguments 😠\n", 1);
			return (1);
		}
	}
	else
		code = all->exit_code; //проинициализировать!
	exit_code = 0 + (unsigned char)code;
//	all->saved_attributes.c_lflag &= ~(ECHO);
//	all->saved_attributes.c_lflag &= ~(ICANON);
//	tcsetattr(0, TCSANOW, &all->saved_attributes);
	ft_putstr_fd("exit 👋\n", 1);
	exit((int)exit_code);
}