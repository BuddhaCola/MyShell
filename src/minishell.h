#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include "parse/parse.h"
#include "utils/get_next_line/get_next_line.h"
#include "utils/libft/libft.h"

#define PROBE printf("here!\n"); //убрать на продакшне!
#define PROMT "minishell 👉"



typedef	struct s_exec
{
	char				**env;
	int 				err;
	t_env 				*environments;
}						t_exec;

typedef	struct			s_todo
{
    t_simple_command    simple_command;
    t_command           command;
	t_exec				exec;
	t_lexer				*lex_buf;
}						t_todo;

int collect_env(t_todo *all, char **env);
void 	handle_signals();

// builtins
void	ft_pwd(void);
int		ft_export(t_todo *all, char **args);
int		ft_pipe(char *program1, char **arg1, char *program2, char **arg2);
int		ft_echo(int argc, char **argv);
int 	ft_env(t_todo *all);

// utils
int		exec_bin(char *path, t_todo *all);
int		redirection(char *filepath, char *program, char **args, int append);

#endif
