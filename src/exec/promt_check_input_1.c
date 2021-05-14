#include "../minishell.h"

void 	get_line(char *buf, t_todo *all)
{
	char	*tmp;

	tmp = all->hist_curr->temp;
	all->hist_curr->temp = ft_strjoin(all->hist_curr->temp, buf);
	free(tmp);
}

int	symbol_newline(t_todo *all)
{
	char	*tmp;

	tcsetattr(0, TCSANOW, &all->saved_attributes);
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

int	up_down_arrows(t_todo *all, char *buf)
{
	if (!(ft_strcmp(buf, "\e[B")))
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

int	ft_backspace(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len > 0)
	{
		tputs(cursor_left, 1, ft_putchar);
		tputs(tigetstr("ed"), 1, ft_putchar);
		str[len - 1] = '\0';
	}
	return (0);
}

int 	check_input(char *buf, t_todo *all)
{
	if (ft_isprint(*buf))
	{
		get_line(buf, all);
		ft_putstr_fd(buf, 1);
		return (0);
	}
	else if (*buf == '\n')
		return (symbol_newline(all));
	else if (*buf == '\177')
		return (ft_backspace(all->hist_curr->temp));
	else if (*buf == '\3')
		return (ctrlc(all));
	else if (*buf == '\4')
		return (ctrld(all));
	else if (!(ft_strcmp(buf, "\e[B")) || !(ft_strcmp(buf, "\e[A")))
		return (up_down_arrows(all, buf));
	return (0);
}
