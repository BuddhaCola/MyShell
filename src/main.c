#include "minishell.h"

void	sigint_handler(int sig_num)
{
	if (sig_num == SIGINT)
		ft_putchar_fd('\n', 2);
	else if (sig_num == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", 2);
}

int	load_up(t_todo *all, char **env)
{
	char	*pwd;

	all->environments = clone_env(env, NULL);
	if (!all->environments)
		return (-1);
	set_shlvl(all);
	pwd = 0;
	pwd = getcwd(pwd, 0);
	env_set_value(all, "PWD", pwd);
	env_set_value(all, "?", "0");
	env_set_value(all, "OLDPWD", NULL);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigint_handler);
	signal(SIGTERM, sigint_handler);
	free(pwd);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_todo		all;

	(void)argc;
	(void)argv;
	ft_bzero(&all, sizeof(all));
	load_up(&all, env);
	promt(&all);
	return (0);
}
