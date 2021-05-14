#include "../minishell.h"

t_history 	*hist_new(char *content)
{
	t_history	*new;

	new = malloc(sizeof(t_history));
	new->temp = content;
	new->next = NULL;
	new->prev = NULL;
	new->orig = NULL;
	return (new);
}

void	hist_add(t_history **lst, t_history *new)
{
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	if (new)
	{
		while ((*lst)->next)
			*lst = (*lst)->next;
		(*lst)->next = new;
		new->prev = *lst;
	}
}

void	hist_move_to_end(t_todo *all)
{
	while (all->hist_curr->next)
		all->hist_curr = all->hist_curr->next;
}
