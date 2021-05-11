#include "minishell.h"

int	termcap_stuff(t_todo *all)
{
	struct termios	new_attributes;

	if(!isatty(0))
		ft_putstr_fd("not a terminal!\n", 1);
	if (tcgetattr(0, &all->saved_attributes) == -1)
		return (-1);
	tcgetattr(0, &new_attributes);
	new_attributes.c_lflag &= ~(ECHO);
	new_attributes.c_lflag &= ~(ISIG);
	new_attributes.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &new_attributes);
	if (tgetent(0, "xterm-256color") != 1)
	{
		ft_putstr_fd("error on tgetent\n", 1);
		exit(-1);
	}
	return (0);
}

void 	get_line(char *buf, t_todo *all)
{
	char	*tmp;
	tmp = all->hist_curr->temp;
	all->hist_curr->temp = ft_strjoin(all->hist_curr->temp, buf);
	free(tmp);
}

void	ft_backspace(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len > 0)
	{
		tputs(cursor_left, 1, ft_putchar);
		tputs(tigetstr("ed"), 1, ft_putchar);
		str[len - 1] = '\0';
	}
}

int 	check_input(char *buf, t_todo *all)
{
	static int quote;
	t_history *lst;
	char	*tmp;

	if (ft_isprint(*buf))
	{
		get_line(buf, all);
		ft_putstr_fd(buf, 1);
		return (0);
	}
	else if (*buf == '\n')
	{
		if (!all->hist_curr->orig)
			all->hist_curr->orig = ft_strdup(all->hist_curr->temp);
		else if (*all->hist_curr->temp)
		{
			tmp = ft_strdup(all->hist_curr->temp);
			free(all->hist_curr->temp);
			all->hist_curr->temp = ft_strdup(all->hist_curr->orig);
			hist_move_to_end(all);
			free(all->hist_curr->temp);
			all->hist_curr->temp = tmp;
		}
		return (write(1, "\n", 1));
	}
	else if (*buf == '\177')
		ft_backspace(all->hist_curr->temp);
	else if (*buf == '\3')
	{
		env_set_value(all, "?", "1");
		hist_move_to_end(all);
		free(all->hist_curr->temp);
		all->hist_curr->temp = ft_strdup("");
		tcsetattr(0, TCSANOW, &all->saved_attributes);
		return (write(1, "\n", 1));
	}
	else if (*buf == '\4')
	{
		if (*all->hist_curr->temp == '\0')
		{
//			all->saved_attributes.c_lflag |= (ISIG | ECHO | ICANON);
			tcsetattr(0, TCSANOW, &all->saved_attributes);
			ft_putendl_fd("exit", 1);
			exit(0);
		}
	}
	else if (!(ft_strcmp(buf, "\e[B")))
	{
		if (all->hist_curr->next)
		{
			all->hist_curr = all->hist_curr->next;
			tputs(restore_cursor, 1, ft_putchar);
			tputs(tgetstr("cd", 0), 1, ft_putchar);
			ft_putstr_fd(all->hist_curr->temp, 1);
		}
	}
	else if (!(ft_strcmp(buf, "\e[A")))
	{
		if (all->hist_curr->prev)
		{
			all->hist_curr = all->hist_curr->prev;
			tputs(restore_cursor, 1, ft_putchar);
			tputs(tgetstr("cd", 0), 1, ft_putchar);
			ft_putstr_fd(all->hist_curr->temp, 1);
		}
	}
	return (0);
}

int		promt(t_todo *all)
{
	char	buf[100];
	int 	ret;

	all->lex_buf = malloc(sizeof(t_lexer));
	while (all->environments)
	{
		if (!all->hist_curr || (all->hist_curr && all->hist_curr->temp[0]))
			hist_add(&all->hist_curr, hist_new(ft_strdup("")));
		hist_move_to_end(all);
		termcap_stuff(all);
		ft_putstr_fd(PROMT, 1);
		tputs(save_cursor, 1, ft_putchar);
		while (1)
		{
			ret = read(0, &buf, 100);
			buf[ret] = '\0';
			// printf("ret = %d\n", ret);
			if (check_input(buf, all))
				break;
		}
		if (*all->hist_curr->temp)
		{
//			all->saved_attributes.c_lflag |= (ISIG | ECHO | ICANON);
			tcsetattr(0, TCSANOW, &all->saved_attributes);
			if (!build_tokens(all, all->hist_curr->temp, ft_strlen(all->hist_curr->temp), all->lex_buf))
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
	}
	//at the end of program clean all.
	return (0);
}

int		load_up(t_todo *all, char **env)
{
	char	*pwd;
	if (!(all->environments = clone_env(env, NULL)))
		return (-1);
	set_shlvl(all);
	pwd = 0;
	pwd = getcwd(pwd, 0);
	env_set_value(all, "PWD", pwd);
	env_set_value(all, "?", "0");
	env_set_value(all, "OLDPWD", NULL);
	free(pwd);
	return (0);
}

int		debug_promt(t_todo *all); //убрать 🚧

void sigint_handler(int sig_num)
{
	int stat_loc;

	wait(&stat_loc);
	if (stat_loc == sig_num)
	{
		if (sig_num == SIGINT)
			ft_putchar_fd('\n', 2);
		else if (sig_num == SIGQUIT)
		{
			ft_putstr_fd("Quit: 3\n", 2);
		}
	}
}

int		main(int argc, char **argv, char **env)
{
	t_todo		all;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigint_handler);
	ft_bzero(&all, sizeof(all));
	load_up(&all, env);
	if (argc > 1)
		debug_promt(&all); //убрать 🚧
	else
		promt(&all);
	return (0);
}







//убрать 🚧
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

//char	*ft_dollarsign(char	*str, t_todo *all)
//{
//	int		i;
//	int		len;
//	char	*envp;
//
//	i = 0;
//	if (!*str || !(len = ft_strlen(str)) || *str < 33 || *str > 126)
//		return ("$");
//	while (all->exec.env[i])
//	{
//		if ((envp = ft_envpsearch(all->exec.env[i], str)))
//			return (envp);
//		i++;
//	}
//	return (NULL);
//}

//void test_parse(char *buf, t_todo *all)
//{
//	int i = -1;
//	while (buf[++i])
//	{
//		if (buf[i] == '!')
//			execution(&buf[i+1], all);
//		else if (buf[i] == '?')
//		else if (buf[i] == '|')
//		{
//			char **args = ft_split(&buf[i+1], ' ');
//			ft_pipe(args[0], 0, args[1], 0);
//		}
//		else if (buf[i] == '>')
//			redirection("./test", "/bin/cat", 0, 2);
//		else if (buf[i] == 'x')
//			ft_export(all, buf + 2);
//		else if (buf[i] == 'e')
//			ft_env(all);
//		else if (buf[i] == 'p')
//			print_env(all);
//		else if (buf[i] == 'w')
//		{
//			printf("%s\n", buf = path_parse(all, "ls"));
//		}
//	}
//	free(buf);
//}

//int     ft_exit(t_todo *all)
//{
//	all->saved_attributes.c_lflag &= ~(ECHO);
//	all->saved_attributes.c_lflag &= ~(ICANON);
//	tcsetattr(0, TCSANOW, &all->saved_attributes);
//	return (0);
//}
