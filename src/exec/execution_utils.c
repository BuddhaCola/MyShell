#include "../minishell.h"

int is_builtin(char *path)
{
	if (!path)
		return (0);
	char *builtins[8];
	int i;

	i = 0;
	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "pwd";
	builtins[3] = "export";
	builtins[4] = "unset";
	builtins[5] = "env";
	builtins[6] = "exit";
	builtins[7] = NULL;
	while (builtins[i])
		if (!ft_strcmp(builtins[i++], path))
			return (1);
	return (0);
}

int do_builtin(char *path, t_todo *all)
{
	if (!(ft_strcmp(path, "echo")))
		return (ft_echo(all));
	else if (!(ft_strcmp(path, "cd")))
		return (ft_cd(all));
	else if (!(ft_strcmp(path, "pwd")))
		return (ft_pwd());
	else if (!(ft_strcmp(path, "export")))
		return (ft_export(all));
	else if (!(ft_strcmp(path, "unset")))
		return (ft_unset(all));
	else if (!(ft_strcmp(path, "env")))
		return (ft_env(all));
	else if (!(ft_strcmp(path, "exit")))
		return (ft_exit(all));
	return (0);
}

char *try_open(t_todo *all)
{
	int		fd;
	char	*bin_location;

	bin_location = NULL;
	fd = open(all->to_execute->cmds->cmd_str, O_RDONLY);
	if (fd != -1 && !ft_strchr("./", all->to_execute->cmds->cmd_str[ft_strlen(all->to_execute->cmds->cmd_str) - 1]))
	{
		bin_location = ft_strdup(all->to_execute->cmds->cmd_str);
		close(fd);
		return (bin_location);
	}
	return (bin_location);
}

int	try_rel_abs_path(t_todo *all)
{
	char	*bin_location;

	bin_location = try_open(all);
	if (bin_location)
		return (start_process(all, bin_location));
	else if (ft_strchr("./", all->to_execute->cmds->cmd_str[ft_strlen(all->to_execute->cmds->cmd_str) - 1]))
	{
		errorhandle(all, all->to_execute->cmds->cmd_str, "is a directory", "126");
		return (126);
	}
	return (0);
}