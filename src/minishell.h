#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include "parse/parse.h"
#include "./utils/get_next_line/get_next_line.h"
#include "utils/libft/libft.h"

#define PROBE printf("here!\n"); //убрать на продакшне!
#define PROMT "minishell 👉"

typedef struct	s_env
{
	char *name;
	char *value;
}				t_env;

typedef struct  s_simple_command
{
    int         number_of_available_arguments;
    int         number_of_arguments;
    char        **arguments;
}               t_simple_command;

typedef struct          s_command
{
    int                 number_of_available_simle_commands;
    int                 number_of_simple_commands;
	t_simple_command    **simple_commands;
    char                *out_file;
    char                *input_file;
    char                *err_file;
    int                 background;
}                       t_command;

typedef	struct s_exec
{
	char				**env;
	int 				err;
	t_env 				*environments;
}						t_exec;


typedef	struct  s_todo
{
    t_simple_command    simple_command;
    t_command           command;
	t_exec				exec;
}               t_todo;

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