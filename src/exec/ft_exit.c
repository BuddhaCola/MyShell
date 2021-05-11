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

int ft_exit(t_todo *all)
{
	unsigned char	exit_code;
	int 			code;

	if (all->to_execute->cmds->args && all->to_execute->cmds->args[1])
	{
		if (ft_checkforbiddensymbols_exit(all->to_execute->cmds->args[1]))
		{
			errorhandle(all, all->to_execute->cmds->args[0], "numeric argument required", NULL);
			exit (-1);
		}
		else
			code = ft_atoi(all->to_execute->cmds->args[1]);
		if (all->to_execute->cmds->args[2])
		{
			errorhandle(all, all->to_execute->cmds->args[0], "too many arguments", NULL);
			return (1);
		}
	}
	else
		code = all->exit_code; //проинициализировать!
//	tcsetattr(0, TCSANOW, &all->saved_attributes);
	all->saved_attributes.c_lflag |= (ISIG | ECHO | ICANON);
	tcsetattr(0, TCSANOW, &all->saved_attributes);
	exit_code = 0 + (unsigned char)code;
	ft_putstr_fd("exit 🚜\n", 1);
	exit((int)exit_code);
}