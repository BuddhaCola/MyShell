#include "../minishell.h"

//returns -1 if error was found
int build_execute_lst(t_todo *all, char *line, int size
,t_lexer *lexer_list)
{
	tokenize(line, size, lexer_list);
	if(check_syntax(lexer_list->tok_list))
	{
		lexer_destroy(all->lex_buf);
		return -1;
	}
	parse_pipes(all);
	printf("%s\n", all->parse_utils->pipelist->tok_lst->data);
	dereference_the_value(all);
	printf("%s\n", all->parse_utils->pipelist->tok_lst->data);


	destroy_parse_pipes(all);
	lexer_destroy(all->lex_buf);

	//free parse_utils struct at the end
	free(all->parse_utils);
	return 0;
}
