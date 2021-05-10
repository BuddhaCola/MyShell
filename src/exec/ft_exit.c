#include "../minishell.h"

static int		ft_checkforbiddensymbols_exit(char *str)
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

	if (args && args[1])
	{
		if (ft_checkforbiddensymbols_exit(args[1]))
		{
			ft_putstr_fd("exit: numeric argument required 😠\n", 1);
			exit (-1);
		}
		else
			code = ft_atoi(args[1]);
		if (args[2])
		{
			errorhandle(all, all->to_execute->cmds->args[0], "too many arguments", "1");
			return (0);
		}
	}
	else
		code = all->exit_code; //проинициализировать!
	tcsetattr(0, TCSANOW, &all->saved_attributes);
	exit_code = 0 + (unsigned char)code;
	ft_putstr_fd("exit 🚜\n", 1);
	exit((int)exit_code);
}