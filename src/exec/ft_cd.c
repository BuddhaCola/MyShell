#include "../minishell.h"

int	ft_cd(t_todo *all)
{
	int		ret;
	char	*home;

	if (all->to_execute->cmd->args[1])
	{
		if (!ft_strcmp(all->to_execute->cmd->args[1], "~"))
			ret = chdir(env_get_value(all, "HOME"));
		else
			ret = chdir(all->to_execute->cmd->args[1]);
	}
	else
	{
		home = env_get_value(all, "HOME");
		if (home)
			ret = chdir(home);
		else
		{
			ft_putstr_fd("bash: cd: HOME not set\n", 1);
			ret = 1;
		}
	}
	return (ret);
}