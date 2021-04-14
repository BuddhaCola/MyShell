#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>

#include "./utils/get_next_line/get_next_line.h"
#include "utils/libft/libft.h"

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
}						t_exec;


typedef	struct  s_todo
{
    t_simple_command    simple_command;
    t_command           command;
	t_exec				exec;
}               t_todo;

// builtins
void	ft_pwd();
void	printenv(char **env);
int		ft_echo(char *str, t_todo *all);
int		ft_pipe(char *p1, char *p2);

// utils
char	*ft_dollarsign(char	*str, t_todo *all);
int		exec_bin(char *path, t_todo *all);