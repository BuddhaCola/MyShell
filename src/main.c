/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtaylor <wtaylor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 18:15:43 by wtaylor           #+#    #+#             */
/*   Updated: 2021/04/20 21:35:07 by wtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     termcap_stuff(t_todo *all)
{
	struct termios	new_attributes;
	char			*termtype;

	termtype = getenv("TERM"); //аккуратнее с этим дерьмом!
	if(!isatty(0))
		printf("not a terminatl!\n");
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
int 	check_input(char *buf, char **line, t_todo *all)
{
	static int quote;

	if (ft_isprint(*buf))
	{
//		if (ft_strchr("/'/", *buf))
//			quote = 1;
		get_line(buf, line);
		ft_putstr_fd(buf, 1);
		return (0);
	}
	else if (*buf == '\n')
	{
//		if (quote == 1)
//			return (write(1, "\n", 1));
//		else
		{
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
	{
		ft_putstr_fd("you pressed UP   | Great job! 👍", 1);
					tputs(restore_cursor, 1, ft_putchar);
	}
	else if (!(ft_strcmp(buf, "\e[B")))
	{
			ft_putstr_fd("you pressed DOWN | Great job! 👍", 1);
						tputs(restore_cursor, 1, ft_putchar);
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
		line = ft_strdup("");
		while (1)
		{
			ret = read(0, &buf, 100);
			buf[ret] = '\0';
			if (check_input(buf, &line, all))
				break;
		}
		if (*line)
		{
			tcsetattr(0, TCSANOW, &all->saved_attributes);
			lexer_build(line, ft_strlen(line), all->lex_buf);
			parse(all);
//			free(line);
			exec_bin(all->to_execute->cmd->cmd_str, all);
		}
		if (*line)
			free(line);
//		reset_parser(all);
	}
	//at the end of program clean all.
	return (0);
}

int		debug_promt(t_todo *all); //убрать 🚧

int		main(int argc, char **argv, char **env)
{
	t_todo		all;

	ft_bzero(&all, sizeof(all));
	if (!(all.environments = clone_env(env, NULL)))
		return (-1);
	env = all.environments;
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
		buf[ret] = '\0';
		lexer_build(buf, ret, all->lex_buf);
		parse(all);
		exec_bin(all->simple_command_list->cmd->cmd_str, all);
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
//			printf("%d\n", all->exec.err);
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
