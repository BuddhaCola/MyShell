#include "../minishell.h"

int	cd_oldpwd(t_todo *all)
{
	char	*oldpwd;
	int		ret;

	oldpwd = env_get_value(all, "OLDPWD");
	if (!oldpwd)
	{
		errorhandle(all, all->cur_cmds->args[0], "OLDPWD not set", "0");
		return (1);
	}
	ft_putendl_fd(oldpwd, 1);
	ret = chdir(oldpwd);
	return (ret);
}

int	cd_home(t_todo *all)
{
	char	*home;
	int		ret;

	home = env_get_value(all, "HOME");
	if (home)
		ret = chdir(home);
	else
	{
		ret = 1;
		errorhandle(all, all->cur_cmds->args[0], "HOME not set", NULL);
	}
	return (ret);
}

int	ft_cd(t_todo *all)
{
	int		ret;
	char	*oldpwd;

	if (all->cur_cmds->args[1]
		&& ft_strcmp(all->cur_cmds->args[1], "~"))
		ret = chdir(all->cur_cmds->args[1]);
	else if (!all->cur_cmds->args[1]
		|| !ft_strcmp(all->cur_cmds->args[1], "~"))
		ret = cd_home(all);
	if (!ft_strcmp(all->cur_cmds->args[1], "-"))
		ret = cd_oldpwd(all);
	if (ret == -1)
	{
		errorhandle(all, all->cur_cmds->args[0], all->cur_cmds->args[1], NULL);
		ret = 1;
	}
	if (ret == 0)
	{
		oldpwd = NULL;
		oldpwd = getcwd(oldpwd, 0);
		env_set_value(all, "OLDPWD", env_get_value(all, "PWD"));
		env_set_value(all, "PWD", oldpwd);
		free(oldpwd);
	}
	return (ret);
}
