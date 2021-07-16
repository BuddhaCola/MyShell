#include "../minishell.h"

static int	ft_checkforbiddensymbols_exit(char *str)
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

int	check_exit_args(t_todo *all)
{
	int	code;

	if (ft_checkforbiddensymbols_exit(all->cur_cmds->args[1]))
	{
		errorhandle(all, all->cur_cmds->args[0],
			"numeric argument required", NULL);
		exit (-1);
	}
	else
		code = ft_atoi(all->cur_cmds->args[1]);
	if (all->cur_cmds->args[2])
	{
		errorhandle(all, all->cur_cmds->args[0],
			"too many arguments", NULL);
		return (1);
	}
	return (code);
}

int	ft_exit(t_todo *all)
{
	unsigned char	exit_code;
	int				code;

	if (all->cur_cmds->args && all->cur_cmds->args[1])
	{
		code = check_exit_args(all);
		if (code == 1)
			return (1);
	}
	else
		code = all->exit_code;
	all->saved_attributes.c_lflag |= (ISIG | ECHO | ICANON);
	tcsetattr(0, TCSANOW, &all->saved_attributes);
	exit_code = 0 + (unsigned char)code;
	ft_putstr_fd("exit 🚜\n", 1);
	exit((int)exit_code);
}
