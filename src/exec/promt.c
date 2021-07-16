#include "../minishell.h"

int	termcap_stuff(t_todo *all)
{
	struct termios	new_attributes;

	if (!isatty(0))
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

void	line_parse_and_execute(t_todo *all)
{
	tcsetattr(0, TCSANOW, &all->saved_attributes);
	if (!build_tokens(all, all->hist_curr->temp,
			ft_strlen(all->hist_curr->temp), all->lex_buf))
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

int	promt(t_todo *all)
{
	char	buf[100];
	int		ret;

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
			if (check_input(buf, all))
				break ;
		}
		if (*all->hist_curr->temp)
			line_parse_and_execute(all);
	}
	return (0);
}
