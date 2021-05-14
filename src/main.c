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

int		debug_promt(t_todo *all)
{
	char	buf[1000];
	int 	ret;

	all->lex_buf = malloc(sizeof(t_lexer));
	while (all->environments)
	{
		ft_putstr_fd(PROMT, 1);
		ret = read(0, &buf, 1000);
		//TODO check ret from read
		buf[ret] = '\0';
		if (!build_tokens(all, buf, ret, all->lex_buf))
		{
			while (all->parse_utils->cur_tok)
			{
				parse_pipes(all);
				dereference_the_value(all);
				build_to_execute_lst(all);
				execution(all);
				destroy_to_execute_lst(all);
				destroy_parse_pipes(all);
			}
			lexer_destroy(all->lex_buf);
			free(all->parse_utils);
		}
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_todo		all;

	(void)argc;
	(void)argv;
	ft_bzero(&all, sizeof(all));
	load_up(&all, env);

	if (argc > 1)
		debug_promt(&all);
	else
		promt(&all);
	return (0);
}
