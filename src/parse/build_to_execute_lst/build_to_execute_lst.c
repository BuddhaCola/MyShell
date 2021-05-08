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
}

static void get_cmd_str(t_todo *all)
{

}

void build_to_execute_lst(t_todo *all)
{
	t_pipelist *pipe_lst_elem;
	pipe_lst_elem = all->parse_utils->pipelist;
	t_tok *tok;

	//for every pipe_elem
	while (pipe_lst_elem)
	{
		tok = pipe_lst_elem->tok_lst;
		//for every token in pipe_elem
		get_cmd_str(all);
		tok = tok->next;
		while (tok)
		{

			tok = tok->next;
		}
		pipe_lst_elem = pipe_lst_elem->next;
	}
}

void destroy_to_execute_lst(t_todo *all)
{






	free(all->to_execute);
}
