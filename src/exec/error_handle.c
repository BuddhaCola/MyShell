#include "../minishell.h"

int	errorhandle(t_todo *all, char *program_name, char *uniqe_error, char *code)
{
	ft_putstr_fd(PROMT, 1);
	ft_putstr_fd(": ", 1);
	if (program_name)
		ft_putstr_fd(program_name, 1);
	ft_putstr_fd(": ", 1);
	if (uniqe_error)
		ft_putendl_fd(uniqe_error, 1);
	else
		ft_putendl_fd(strerror(errno), 1);
	env_set_value(all, "?", code);
	return (0);
}