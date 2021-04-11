#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "parse/parse.h"

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

typedef	struct  s_todo
{
    t_simple_command    simple_command;
    t_command           command;
}               t_todo;

size_t	ft_strlen(char *str);
char	*ft_strjoin(char *org, char *append);
size_t	ft_strlcat(char *dst, char *src, size_t dsize);

// builtins
void	ft_pwd()