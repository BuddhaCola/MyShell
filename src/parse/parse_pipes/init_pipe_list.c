#include "../../minishell.h"

t_pipelist  *get_next_pipe_list_elem(t_pipelist *pipe_lst)
{
    pipe_lst->next = malloc(sizeof(t_pipelist));
    pipe_lst->next->tok_lst = malloc(sizeof(t_tok));
    pipe_lst->next->next = NULL;
    init_tok(pipe_lst->next->tok_lst);
    return (pipe_lst->next);
}

t_tok   *get_next_tok_list_elem(t_tok *lst)
{
    lst->next = malloc(sizeof(t_tok));
    lst->next->data = NULL;
    lst->next->type = 0;
    lst->next->next = NULL;
    return (lst->next);
}

void init_tok(t_tok *lst)
{
    lst->type = 0;
    lst->next = NULL;
    lst->data = NULL;
}

void    init_pipe_list(t_todo *all, t_tok **src_lst, t_tok **pipe_lst_tok, t_pipelist **pipelist)
{
    all->parse_utils->pipelist = malloc(sizeof(t_pipelist));
    all->parse_utils->pipelist->next = NULL;
    all->parse_utils->pipelist->tok_lst = malloc(sizeof(t_tok));
    init_tok(all->parse_utils->pipelist->tok_lst);
    *src_lst = all->parse_utils->cur_tok;
    *pipe_lst_tok = all->parse_utils->pipelist->tok_lst;
    *pipelist = all->parse_utils->pipelist;
}