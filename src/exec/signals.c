#include "../minishell.h"

void 	handle_sigint()
{
//	write(1, "minishell 👉 ", 15);
}

void	handle_eof()
{
	exit(1);
}

void 	handle_signals()
{
//	signal(SIGINT, &handle_sigint);
//	signal(4, &handle_eof);
	return ;
}