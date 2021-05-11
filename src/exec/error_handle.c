#include "../minishell.h"

int	errorhandle(t_todo *all, char *program_name, char *uniqe_error, char *code)
{
	ft_putstr_fd("minishell", 1);
//	ft_putstr_fd(": ", 1);
	if (program_name)
	{
		ft_putstr_fd(": ", 1);
		ft_putstr_fd(program_name, 1);
	}
	if (uniqe_error)
	{
		ft_putstr_fd(": ", 1);
		ft_putstr_fd(uniqe_error, 1);
	}
	if (errno && ft_strcmp(code, "0"))
	{
//		if (uniqe_error || program_name)
		ft_putstr_fd(": ", 1);
		ft_putstr_fd(strerror(errno), 1);
	}
	ft_putstr_fd("\n", 1);
	if (code)
		env_set_value(all, "?", code);
	return (0);
}