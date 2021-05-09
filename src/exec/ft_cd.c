#include "../minishell.h"

int	cd_home(t_todo *all)
{
	char	*home;
	int		ret;

	home = env_get_value(all, "HOME");
	if (home)
		ret = chdir(home);
	else
	{
		ft_putstr_fd("bash: cd: HOME not set\n", 1);
		ret = 1;
	}
	return (ret);
}

int	ft_cd(t_todo *all)
{
	int		ret;
	char	*home;

	env_set_value(all, "OLDPWD", env_get_value(all, "PWD"));
	if (all->to_execute->cmd->args[1]
		&& ft_strcmp(all->to_execute->cmd->args[1], "~"))
		ret = chdir(all->to_execute->cmd->args[1]);
	else
		ret = cd_home(all);
	if (ret == -1)
	{
		printf("bash: cd: %s: No such file or directory\n",
			all->to_execute->cmd->args[1]);
		fflush(stdout);
	}
	home = NULL;
	home = getcwd(home, 0);
	env_set_value(all, "PWD", home);
	free(home);
	if (ret == 0)
		ret = 1;
	return (ret);
}
