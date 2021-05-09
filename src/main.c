#include "minishell.h"

int     termcap_stuff(t_todo *all)
{
	struct termios	new_attributes;
	char			*termtype;

	termtype = getenv("TERM"); //это говно!
	if(!isatty(0))
		ft_putstr_fd("not a terminatl!\n", 1);
	if (tcgetattr(0, &all->saved_attributes) == -1)
		return (-1);
	ft_memcpy(&new_attributes, &all->saved_attributes, sizeof(new_attributes));
	new_attributes.c_lflag &= ~(ECHO);
	new_attributes.c_lflag &= ~(ISIG);
	new_attributes.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &new_attributes);
	if (tgetent(0, termtype) != 1)
		return (write(1, "error on tgetent\n", 17));
	return (0);
}

void 	get_line(char *buf, char **line)
{
	char	*tmp;
	tmp = *line;
	*line = ft_strjoin(*line, buf);
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

//void	history_pressed_enter(t_history **current, char *data)
//{
//	t_history *new;
//
//	new = malloc(sizeof(t_history *));
//	(*current)->next = new;
//	(*current)->data = ft_strdup("data");
//	new->prev = *current;
//	*current = new;
//	(*current)->next = NULL;
//}

t_history 	*hist_new(char *content)
{
	t_history	*new;

	if (!(new = malloc(sizeof(t_history))))
		return (NULL);
	new->data = content;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	histadd_front(t_history **lst, t_history *new) {
	if (!lst)
	{
		*lst = new;
		return ;
	}
	if (new)
	{
		new->next = *lst;
		(*lst)->prev = new;
		*lst = new;
	}
}

//t_history	*hist_move_up(t_history *current)
//{
//	current = current->prev;
//}

void print_hist(t_todo *all)
{
	t_history *curr = all->hist_curr;
	if (!curr)
		ft_putstr_fd("no curr!\n", 1);
	while (curr->data)
	{
//		PROBE
		printf("|%s|->", (*curr).data);
		fflush(stdout);
		curr = curr->next;
	}
}

int 	check_input(char *buf, char **line, t_todo *all)
{
	static int quote;
	t_history *lst;

	if (ft_isprint(*buf))
	{
		get_line(buf, line);
		ft_putstr_fd(buf, 1);
		return (0);
	}
	else if (*buf == '\n')
	{
		{
//			if (!all->head)
//			{
//				if (*line)
//				{
//					all->head = hist_new(ft_strdup(*line));
//					all->hist_curr = all->head;
//				}
//			}
//			else
//				(histadd_front(&all->head, hist_new(ft_strdup(*line))));
			return (write(1, "\n", 1));
		}
	}
	else if (*buf == '\177')
		ft_backspace(*line);
	else if (*buf == '\3')
	{
		free(*line);
		*line = ft_strdup("");
		return (write(1, "\n", 1));
	}
	else if (*buf == '\4')
	{
			if (**line == '\0')
				ft_exit(NULL, all);
	}
	else if (!(ft_strcmp(buf, "\e[A")))
//	else if (!(ft_strcmp(buf, "1")))
	{
		//UP
		if (all->hist_curr && all->hist_curr->prev)
		{
//			print_hist(all);
			all->hist_curr = all->hist_curr->prev;
			tputs(restore_cursor, 1, ft_putchar);
			tputs(tgetstr("cd", 0), 1, ft_putchar);
			ft_putstr_fd(all->hist_curr->data, 1);
//			printf("%s", all->hist_curr->data);
//			fflush(stdout);
		}
//		else
//			all->hist_curr = all->head;
	}
//	else if (!(ft_strcmp(buf, "2")))
	else if (!(ft_strcmp(buf, "\e[B")))
	{
		if (all->hist_curr && all->hist_curr->next)
		{
//			print_hist(all);
			all->hist_curr = all->hist_curr->next;
			tputs(restore_cursor, 1, ft_putchar);
			tputs(tgetstr("cd", 0), 1, ft_putchar);
			printf("%s", all->hist_curr->data);
			fflush(stdout);
		}
//		tputs(restore_cursor, 1, ft_putchar);
	}
	return (0);
}

int		promt(t_todo *all)
{
	char	buf[100];
	int 	ret;
	char	*line;

	all->lex_buf = malloc(sizeof(t_lexer));

	while (all->environments)
	{
		termcap_stuff(all);
		ft_putstr_fd(PROMT, 1);
		tputs(save_cursor, 1, ft_putchar);
//		line = ft_strdup("");
		all->head = hist_new("");
		histadd_front(&all->head, hist_new(ft_strdup("")));
		all->hist_curr = all->head;
		while (1)
		{
			ret = read(0, &buf, 100);
			buf[ret] = '\0';
			if (check_input(buf, &all->head->data, all))
				break;
		}
		if (*all->head->data)
		{
//			print_hist(all);
//			histadd_front(&all->head, hist_new(ft_strdup(all->head->data)));
			tcsetattr(0, TCSANOW, &all->saved_attributes);
			lexer_build(all->head->data, ft_strlen(all->head->data), all->lex_buf);
			parse(all);
//			free(all->head->data);
			exec_bin(all);
		}
		if (*all->head->data)
			free(all->head->data);
//		reset_parser(all);
	}
	//at the end of program clean all.
	return (0);
}

int		load_up(t_todo *all, char **env)
{
	char **oldpwd;
	if (!(all->environments = clone_env(env, NULL)))
		return (-1);
	set_shlvl(all);
	env_set_value(all, "OLDPWD", NULL);
	return (0);
}

int		debug_promt(t_todo *all); //убрать 🚧

int		main(int argc, char **argv, char **env)
{
	t_todo		all;

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
//		if (check_input(buf, &buf, all))
//			break;
		lexer_build(buf, ret, all->lex_buf);
		parse(all);
		exec_bin(all);
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
//			exec_bin(&buf[i+1], all);
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
