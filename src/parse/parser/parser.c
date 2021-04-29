#include "../../minishell.h"

//DONE
static void init_cmd(t_todo *all)
{
    all->to_execute->cmd->cmd_str = NULL;
    all->to_execute->cmd->args = NULL;
    all->to_execute->cmd->flg_pipe = 0;
    all->to_execute->cmd->input_files = NULL;
    all->to_execute->cmd->output_files = NULL;
    all->to_execute->cmd->double_greater_output_files = NULL;
    all->to_execute->cmd->next = NULL;
}

//DONE
static void parse_build(t_todo *all)
{
    all->to_execute = malloc(sizeof(t_to_execute));
    all->to_execute->cmd = (void *)malloc(sizeof(t_cmd));
    init_cmd(all);
    all->cur_tok_list = all->lex_buf->tok_list;
    all->cur_cmd_list = all->to_execute->cmd;
}

//DONE
static int  try_get_cmd_str(t_todo *all)
{
    if (all->cur_tok_list && (all->cur_tok_list->type == CHAR_GENERAL))
        all->to_execute->cmd->cmd_str = path_parse(all, all->cur_tok_list->data);
    else
        return (-1);
    return (0);
}

//DONE
//get args from tokens
static int  try_get_args(t_todo *all)
{
    size_t  i;
    size_t  k;
    t_tok   *tok_list_cpy;

    tok_list_cpy = all->cur_tok_list;
    i = 0;
    k = 0;
    //count tokens
    while (tok_list_cpy && tok_list_cpy->type == CHAR_GENERAL)
    {
        i++;
        tok_list_cpy = tok_list_cpy->next;
    }
    //if i > write them to 2d str array
    if (i > 0)
    {
        all->cur_cmd_list->args = malloc(sizeof(char *) * (i + 1));
        all->cur_cmd_list->args[k] = path_parse(all, all->cur_tok_list->data);
        all->cur_tok_list = all->cur_tok_list->next;
        k++;
        i--;
        //copy tokens to 2d array if exist
        while (i--)
        {
            all->cur_cmd_list->args[k] = ft_strdup(all->cur_tok_list->data);
            k++;
            all->cur_tok_list = all->cur_tok_list->next;
        }
        //terminate 2d cmd array
        all->cur_cmd_list->args[k] = NULL;
    }
    return (0);
}

//DONE
//iter cmd list
static void iter_to_new_cmd_list(t_todo *all)
{
    all->cur_cmd_list->next = malloc(sizeof(t_cmd));
    all->cur_cmd_list = all->cur_cmd_list->next;
    all->cur_cmd_list->cmd_str = NULL;
    all->cur_cmd_list->args = NULL;
    all->cur_cmd_list->flg_pipe = 0;
    all->cur_cmd_list->input_files = NULL;
    all->cur_cmd_list->output_files = NULL;
    all->cur_cmd_list->double_greater_output_files = NULL;
    all->cur_cmd_list->next = NULL;
}

//DONE
static void init_2d_file_array(char ***str)
{
    *str = malloc (sizeof(char *));
    **str = NULL;
}

//write
static void write_to_2d_filename(char ***str)
{
    char **str_ptr;

    str_ptr = *str;
    while (str_ptr)
    {

    }

}

//write files to the 2d array
static int try_to_get_filename(t_todo *all, int io_mode)
{
    //write to **input
    if (io_mode == 0)
    {
        if (all->cur_tok_list->type == CHAR_GENERAL)
        {
            init_2d_file_array(&all->cur_cmd_list->input_files);
            all->cur_tok_list = all->cur_tok_list->next;
        }
        else
        {
            //print error type
            return (-1);
        }
    }
    //write to **output
    if (io_mode == 1)
    {
        if (all->cur_tok_list->type == CHAR_GENERAL)
        {
            init_2d_file_array(&all->cur_cmd_list->output_files);
            all->cur_tok_list = all->cur_tok_list->next;
        }
        else
        {
            //print error type
            return (-1);
        }
    }
    //write to **double_greater_output_files
    if (io_mode = 2)
    {
        if (all->cur_tok_list->type == CHAR_GENERAL)
        {
            init_2d_file_array(&all->cur_cmd_list->double_greater_output_files);
            all->cur_tok_list = all->cur_tok_list->next;
        }
        else
        {
            //print error type
            return (-1);
        }
    }
    return (0);
}

//дописать правило для ">>"
static int check_non_general(t_todo *all)
{
    while (all->cur_tok_list && (all->cur_tok_list->type == CHAR_GENERAL || all->cur_tok_list->type == CHAR_GREATER
    || all->cur_tok_list->type == CHAR_LESSER || all->cur_tok_list == CHAR_DGREATER))
    {
        if (all->cur_tok_list && all->cur_tok_list->type != CHAR_GENERAL)
        {
            if (all->cur_tok_list->type == CHAR_GREATER)
            {
                all->cur_tok_list = all->cur_tok_list->next;
                try_to_get_filename(all, 1);
            }
            else if (all->cur_tok_list->type == CHAR_LESSER)
            {
                all->cur_tok_list = all->cur_tok_list->next;
                try_to_get_filename(all, 0);
            }
            else if (all->cur_tok_list->type == CHAR_DGREATER)
            {
                all->cur_tok_list = all->cur_tok_list->next;
                try_to_get_filename(all, 2);
            }
            return (1);
        }
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

static void destroy_2d(char ***str) {
    char **ptr;

    if (*str != NULL)
    {
        ptr = *str;
        while (ptr) {
            free(ptr);
            ptr++;
        }
        free(*str);
    }
}

//destroy cmd_list
void destroy_cmd_list(t_cmd *list)
{
    if (list != NULL)
    {
        free(list->cmd_str);
        destroy_2d(&list->args);
        destroy_2d(&list->input_files);
        destroy_2d(&list->output_files);
        destroy_2d(&list->double_greater_output_files);
        destroy_cmd_list(list->next);
        free(list);
    }
}

//destroy parser at the end of the program
void destroy_parser(t_todo *all)
{
    destroy_cmd_list(all->to_execute->cmd);
    free(all->to_execute);
}
