#include "../../minishell.h"

void		lexer_destroy(t_lexer *list)
{
    if (list == NULL)
        return ;
    tok_destroy(list->tok_list);
}
