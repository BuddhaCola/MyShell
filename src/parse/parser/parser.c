#include "../../minishell.h"

//update cur_simple_cmd_list
//and update cur_tok_list
static void iterate_simple_cmd_list(t_todo *all)
{

}

//update cur_tok_list
static void iterate_token_list(t_todo *all)
{

}

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
    if (all->cur_tok_list && (all->cur_tok_list->type == CHAR_GENERAL))
    {
        all->cur_simple_command_list->cmd->cmd_str = path_parse(all, all->cur_tok_list->data);
//        all->cur_simple_command_list->cmd->cmd_str = ft_strdup(all->cur_tok_list->data);
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
        all->cur_simple_command_list->cmd->args[k] = path_parse(all, all->cur_tok_list->data);
        all->cur_tok_list = all->cur_tok_list->next;
        k++;
        i--;
        //copy toks to 2d
        while (i--)
        {
            all->cur_simple_command_list->cmd->args[k] = ft_strdup(all->cur_tok_list->data);
            k++;
            all->cur_tok_list = all->cur_tok_list->next;
        }
        all->cur_simple_command_list->cmd->args[k] = NULL;
    }
    return (0);
}

static void go_next_simple_cmd_list_elem(t_todo *all)
{
    all->cur_simple_command_list->next = malloc(sizeof(t_custom_list));
    all->cur_simple_command_list = all->cur_simple_command_list->next;
    all->cur_simple_command_list->cmd = malloc(sizeof(t_cmd));
    all->cur_simple_command_list->next = NULL;
    all->cur_simple_command_list->cmd->cmd_str = NULL;
    all->cur_simple_command_list->cmd->args = NULL;
    all->cur_simple_command_list->cmd->flg_pipe_left = 0;
    all->cur_simple_command_list->cmd->flg_pipe_right = 0;
    all->cur_simple_command_list->cmd->flg_redir_in = 0;
    all->cur_simple_command_list->cmd->flg_redir_out = 0;
    all->cur_simple_command_list->cmd->input = 0;
    all->cur_simple_command_list->cmd->output = 0;
    all->cur_simple_command_list->cmd->next = NULL;
}

// add new cmd list and switch to them
static void go_next_cmd_list_elem(t_todo *all)
{
    all->cur_simple_command_list->cmd->next = malloc(sizeof(char));
}

static void try_to_get_filenames(t_todo *all, int io_mode)
{
    if (io_mode == 0){} //write to **input
    if (io_mode == 1){} //write to **output
}

//дописать правило для ">>"
static int check_non_general(t_todo *all)
{
    if (all->cur_tok_list && all->cur_tok_list->type != CHAR_GENERAL)
    {
        if (all->cur_tok_list->type == CHAR_GREATER)
        {
            all->cur_simple_command_list->cmd->flg_redir_out = 1;
            try_to_get_filenames(all,1);
            all->cur_tok_list = all->cur_tok_list->next;
        }
        else if (all->cur_tok_list->type == CHAR_LESSER)
        {
            all->cur_simple_command_list->cmd->flg_redir_in = 1;
            try_to_get_filenames(all,0);
            all->cur_tok_list = all->cur_tok_list->next;
        }
        else if (all->cur_tok_list->type == CHAR_PIPE)
        {
            go_next_cmd_list_elem(all);
//            all->cur_simple_command_list->cmd;
        }
        return (1);
    }
    return (0);
}

static void try_get_pipe(t_todo *all)
{

}

//if semiclon iterate_cmd_list
static int check_semicolon(t_todo *all)
{
//    if (semicolon)
//    {
//        return 0;
//    }
    return (1);
}

void parse(t_todo *all)
{
    int semicolon;

    parse_build(all);
    semicolon = 0;
    while (!semicolon) {
        // [cmd]
        try_get_cmd_str(all);
        // [args]
        try_get_args(all);
        // [> filename],[< filename],[>> filename]
        check_non_general(all);
        // [|]
        try_get_pipe(all);
        // [;]
        semicolon = check_semicolon(all);
    }
}

//reset parser after reading
void reset_parser(t_todo *all)
{

}

//destroy parser at the end of the program
void destroy_parser(t_todo *all)
{

}
