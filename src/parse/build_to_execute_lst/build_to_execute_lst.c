#include "../../minishell.h"

static void tok_next_add_to_2d(char **str, t_tok **tok)
{
    *tok = (*tok)->next;
    add_to_2d(&str, *tok);
}

static void main_while(t_tok **tok, t_cmds *cmds)
{
    while (*tok)
    {
        if ((*tok)->type == TOKEN)
            strip_quotes_and_bslashes(&(*tok)->data);
        if ((*tok)->type == CHAR_GREATER)
            tok_next_add_to_2d(cmds->output_files, &(*tok));
        else if ((*tok)->type == CHAR_LESSER)
            tok_next_add_to_2d(cmds->input_files, &(*tok));
        else if ((*tok)->type == CHAR_DGREATER)
            tok_next_add_to_2d(cmds->append_files, &(*tok));
        else
            add_to_2d(&cmds->args, *tok);
        *tok = (*tok)->next;
    }
}

void build_to_execute_lst(t_todo *all)
{
	t_pipelist *pipe_lst_elem;
	pipe_lst_elem = all->parse_utils->pipelist;
	t_tok *tok;
	t_cmds *cmds;

    parse_build(all, &cmds);
	while (pipe_lst_elem)
	{
    	tok = pipe_lst_elem->tok_lst;
		get_cmd_str(cmds, tok);
		tok = tok->next;
        main_while(&tok, cmds);
		pipe_lst_elem = pipe_lst_elem->next;
		if (pipe_lst_elem)
			cmds = get_new_cmds_elem(cmds);
	}
}
