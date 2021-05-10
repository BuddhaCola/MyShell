#include "../minishell.h"

//returns -1 if error was found
int build_execute_lst(t_todo *all, char *line, int size
		, t_lexer *lexer_list)
{
	tokenize(line, size, lexer_list);
	if(check_syntax(lexer_list->tok_list))
	{
		lexer_destroy(all->lex_buf);
		return -1;
	}
	//костыль для cur_tok
	all->parse_utils->cur_tok = all->lex_buf->tok_list;
	parse_pipes(all);
	dereference_the_value(all);
	build_to_execute_lst(all);

	destroy_to_execute_lst(all);
	destroy_parse_pipes(all);
	lexer_destroy(all->lex_buf);

	//free parse_utils struct at the end
	free(all->parse_utils);
	return 0;
}
