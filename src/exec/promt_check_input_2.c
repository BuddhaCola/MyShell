#include "../minishell.h"

int	ctrlc(t_todo *all)
{
	env_set_value(all, "?", "1");
	hist_move_to_end(all);
	free(all->hist_curr->temp);
	all->hist_curr->temp = ft_strdup("");
	tcsetattr(0, TCSANOW, &all->saved_attributes);
	return (write(1, "\n", 1));
}

int	ctrld(t_todo *all)
{
	if (*all->hist_curr->temp == '\0')
	{
		tcsetattr(0, TCSANOW, &all->saved_attributes);
		ft_putendl_fd("exit", 1);
		exit(0);
	}
	return (0);
}
