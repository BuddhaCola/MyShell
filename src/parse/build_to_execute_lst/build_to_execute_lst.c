#include "../../minishell.h"

static void parse_build(t_todo *all)
{
	all->to_execute = malloc(sizeof(t_to_execute));
	all->to_execute->cmds = malloc(sizeof(t_cmds));
	all->to_execute->cmds->cmd_str = NULL;
	all->to_execute->cmds->args = NULL;
	all->to_execute->cmds->input_files = NULL;
	all->to_execute->cmds->output_files = NULL;
	all->to_execute->cmds->append_files = NULL;
	all->to_execute->cmds->next = NULL;
}

static void init_cmds_elem(t_cmds *cmds)
{
    cmds->cmd_str = NULL;
    cmds->args = NULL;
    cmds->input_files = NULL;
    cmds->output_files = NULL;
    cmds->append_files = NULL;
    cmds->next = NULL;
}

static t_cmds *get_new_cmds_elem(t_cmds *cmds)
{
    cmds->next = malloc(sizeof(t_cmds));
    init_cmds_elem(cmds->next);
    return (cmds->next);
}

static void get_cmd_str(t_cmds *cmds, t_tok *tok)
{
    cmds->cmd_str = ft_strdup(tok->data);
    cmds->args = malloc(sizeof(char *) * 2);
    cmds->args[0] = ft_strdup(tok->data);
    cmds->args[1] = NULL;
}

static void add_to_2d(char ***src, t_tok *tok)
{
    char **str;
    char **str_cpy;
    char **new_str;
    char **new_str_cpy;
    size_t old_len;
    str = *src;
    if (str == NULL)
    {
        str = malloc(sizeof(char *) * 1);
        str[0] = NULL;
    }
    old_len = 0;
    str_cpy = str;
    while (*str_cpy)
    {
        old_len++;
        str_cpy++;
    }
    new_str = malloc(sizeof(char *) * (old_len + 2));
    new_str_cpy = new_str;
    str_cpy = str;
    //cpy old data
    while (*str_cpy)
    {
        *new_str_cpy = *str_cpy;
        new_str_cpy++;
        str_cpy++;
    }
    *new_str_cpy = ft_strdup(tok->data);
    new_str_cpy++;
    *new_str_cpy = NULL;
    free(str);
    *src = new_str;
}

void build_to_execute_lst(t_todo *all)
{
    //pipe_elem, tokens
	t_pipelist *pipe_lst_elem;
	pipe_lst_elem = all->parse_utils->pipelist;
	t_tok *tok;
    //to_execute
	t_cmds *cmds;

	//for every pipe_elem
    parse_build(all);
	//get cmds list elem
	cmds = all->to_execute->cmds;
    while (pipe_lst_elem)
	{
		//get new cmds elem;
		cmds = get_new_cmds_elem(cmds);
    	tok = pipe_lst_elem->tok_lst;
		//for every token in pipe_elem
		get_cmd_str(cmds, tok);
		tok = tok->next;
		while (tok)
		{
            if (tok->type == CHAR_GREATER)
                add_to_2d(&cmds->output_files, tok);
            else if (tok->type == CHAR_LESSER)
                add_to_2d(&cmds->input_files, tok);
            else if (tok->type == CHAR_DGREATER)
                add_to_2d(&cmds->append_files, tok);
            else
                add_to_2d(&cmds->args, tok);
            tok = tok->next;
        }
		//next pipe_elem
		pipe_lst_elem = pipe_lst_elem->next;
	}
}

static void destroy_2d(char **str)
{
    char **str_cpy;
    str_cpy = str;
    if (str != NULL)
    {
        while (*str != NULL)
        {
            free(*str);
            str++;
        }
        free(str_cpy);
    }
}

static void destroy_cmds(t_cmds *cmds)
{
    if (cmds != NULL)
    {
        if (cmds->cmd_str != NULL)
            free(cmds->cmd_str);
        destroy_2d(cmds->args);
        destroy_2d(cmds->input_files);
        destroy_2d(cmds->output_files);
        destroy_2d(cmds->append_files);
        destroy_cmds(cmds->next);
        free(cmds);
    }
}

void destroy_to_execute_lst(t_todo *all)
{
    destroy_cmds(all->to_execute->cmds);
	free(all->to_execute);
}
