#include "../../minishell.h"

//DONE
static void init_tok(t_tok *lst)
{
    lst->type = 0;
    lst->next = NULL;
    lst->data = NULL;
}

//DONE
void    init_pipe_list(t_todo *all)
{
    all->parse_utils = malloc(sizeof(t_parse_utils));
    all->parse_utils->pipelist = malloc(sizeof(t_pipelist));
    all->parse_utils->pipelist->next = NULL;
    all->parse_utils->pipelist->tok_lst = malloc(sizeof(t_tok));
    init_tok(all->parse_utils->pipelist->tok_lst);
}

//DONE
t_pipelist  *get_next_pipe_list_elem(t_pipelist *pipe_lst)
{
    pipe_lst->next = malloc(sizeof(t_pipelist));
    pipe_lst->next->tok_lst = malloc(sizeof(t_tok));
    pipe_lst->next->next = NULL;
    init_tok(pipe_lst->next->tok_lst);
    return (pipe_lst->next);
}

//DONE
t_tok   *get_next_tok_list_elem(t_tok *lst)
{
    lst->next = malloc(sizeof(t_tok));
    lst->next->data = NULL;
    lst->next->type = 0;
    lst->next->next = NULL;
    return (lst->next);
}

//parse_pipes
void    parse_pipes(t_todo *all)
{
    t_tok *src_lst;         //last src token
    t_tok *pipe_lst_tok;    //last pipe token
    t_pipelist *pipelist;   //pipe list elem

    //init
    init_pipe_list(all);
    src_lst = all->lex_buf->tok_list;
    pipe_lst_tok = all->parse_utils->pipelist->tok_lst;
    pipelist = all->parse_utils->pipelist;
    //iterate on src tokens
    while (src_lst)
    {
        //get next pipelist elem if char_pipe
        if (src_lst->type == CHAR_PIPE)
        {
            pipelist = get_next_pipe_list_elem(pipelist);
            pipe_lst_tok = pipelist->tok_lst;
            src_lst = src_lst->next;
            continue;
        }
        else
        {
            //get next elem, cpy tokens data and type
            pipe_lst_tok->data = ft_strdup(src_lst->data);
            pipe_lst_tok->type = src_lst->type;
        }
        //get tok after pipe
        if (src_lst->next == NULL || src_lst->type == CHAR_SEMICOLON)
            break;
        if (src_lst->next->type == CHAR_PIPE)
        {
            src_lst = src_lst->next;
            continue;
        }
        pipe_lst_tok = get_next_tok_list_elem(pipe_lst_tok);
        src_lst = src_lst->next;
    }
}

static void delete_tokens(t_tok *tok_elem)
{
    if (tok_elem != NULL)
    {
        free(tok_elem->data);
        delete_tokens(tok_elem->next);
        free(tok_elem);
    }
}


static void delete_all_tokens_in_pipe_lst(t_todo *all)
{
    t_pipelist *pipe_elem;

    pipe_elem = all->parse_utils->pipelist;
    while (pipe_elem)
    {
        delete_tokens(pipe_elem->tok_lst);
        pipe_elem = pipe_elem->next;
    }
}

static void delete_all_pipe_elems(t_pipelist *pipe_elem)
{
    if (pipe_elem != NULL)
    {
        delete_all_pipe_elems(pipe_elem->next);
        free(pipe_elem);
    }
}

void destroy_parse_pipes(t_todo *all)
{
    //delete all tokens along all pipeelems
    delete_all_tokens_in_pipe_lst(all);
    //delete pipeelems
    delete_all_pipe_elems(all->parse_utils->pipelist);
}
