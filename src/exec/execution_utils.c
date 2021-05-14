#include "../minishell.h"

int	errorhandle(t_todo *all, char *program_name, char *uniqe_error, char *code)
{
	ft_putstr_fd("minishell", 2);
	if (program_name)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(program_name, 2);
	}
	if (uniqe_error)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(uniqe_error, 2);
	}
	if (errno && ft_strcmp(code, "0"))
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
	}
	ft_putstr_fd("\n", 2);
	if (code)
		env_set_value(all, "?", code);
	return (0);
}

int	is_builtin(char *path)
{
	char	*builtins[8];
	int		i;

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

int	do_builtin(char *path, t_todo *all)
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

char	*try_open(t_todo *all)
{
	int		fd;
	char	*bin_location;

	bin_location = NULL;
	fd = open(all->cur_cmds->cmd_str, O_RDONLY);
	if (fd != -1 && !ft_strchr("./",
			all->cur_cmds->cmd_str
			[ft_strlen(all->cur_cmds->cmd_str) - 1]))
	{
		bin_location = ft_strdup(all->cur_cmds->cmd_str);
		close(fd);
		return (bin_location);
	}
	return (bin_location);
}

int	try_rel_abs_path(t_todo *all, int *flg)
{
	char	*bin_location;

	*flg = 0;
	bin_location = try_open(all);
	if (bin_location)
	{
		*flg = 1;
		return (start_process(all, bin_location));
	}
	else if (ft_strchr("./", all->cur_cmds->cmd_str
			[ft_strlen(all->cur_cmds->cmd_str) - 1]))
	{
		errorhandle
			(all, all->cur_cmds->cmd_str, "is a directory", NULL);
		*flg = 1;
		return (126);
	}
	return (0);
}
