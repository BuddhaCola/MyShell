#include "../../minishell.h"

static void init_cmd(t_todo *all)
{
    all->simple_command_list->cmd->cmd_str = NULL;
    all->simple_command_list->cmd->args = NULL;
    all->simple_command_list->cmd->flg_pipe_left = 0;
    all->simple_command_list->cmd->flg_pipe_right = 0;
    all->simple_command_list->cmd->flg_redir_in = 0;
    all->simple_command_list->cmd->flg_redir_out = 0;
    all->simple_command_list->cmd->input = 0;
    all->simple_command_list->cmd->output = 0;
    all->simple_command_list->cmd->next = NULL;
}

static void parse_build(t_todo *all)
{
    all->simple_command_list = malloc(sizeof(t_custom_list));
    all->simple_command_list->cmd = (void *)malloc(sizeof(t_cmd));
    all->simple_command_list->next = NULL;
    init_cmd(all);
    all->cur_tok_list = all->lex_buf->tok_list;
    all->cur_simple_command_list = all->simple_command_list;
}

static int  try_get_cmd_str(t_todo *all)
{
    if (all->cur_tok_list && (all->cur_tok_list->data == CHAR_GENERAL))
    {
        all->cur_simple_command_list->cmd->cmd_str = ft_strdup(all->cur_tok_list->data);
        all->cur_tok_list = all->cur_tok_list->next;
    }
    else
    {
        return (-1);
    }
    return (0);
}

static int  try_get_args(t_todo *all)
{
    size_t  i;
    size_t  k;
    t_tok   *tok_list_cpy;

    tok_list_cpy = all->cur_tok_list;
    i = 0;
    k = 0;
    while (tok_list_cpy && tok_list_cpy->type == CHAR_GENERAL)
    {
        i++;
        tok_list_cpy = tok_list_cpy->next;
    }
    if (i != 0)
    {
        all->cur_simple_command_list->cmd->args = malloc(sizeof(char *) * (i + 1));
        //copy toks to 2d
        while (i--)
        {
            all->cur_simple_command_list->cmd->args[k] = ft_strdup(all->cur_tok_list->data);
            k++;
            all->cur_tok_list = all->cur_tok_list->next;
        }
        all->cur_simple_command_list->cmd->args[k] = NULL;
    }
}

static int check_non_general(t_todo *all)
{
    if (all->cur_tok_list->type == CHAR)
    {

        return (-1);
    }
    return (0);
}

static void destroy_parser(t_todo *all)
{

}

void parse(t_todo *all)
{
    int done;

    parse_build(all);
    done = 0;
    while (!done)
    {
        if (try_get_cmd_str(all) < 0)
        {
            return ;
        }
        if (try_get_args(all) < 0)
            return ;
        //check redir in/out or pipeline or semicolon or end_of_toks;
        done = check_non_general(all);
    }
    destroy_parser(all);
}
