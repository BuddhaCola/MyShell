#include "../../minishell.h"

static void cpy_old_data(char ***str_cpy, char ***new_str_cpy)
{
    while (**str_cpy)
    {
        **new_str_cpy = **str_cpy;
        *new_str_cpy = *new_str_cpy + 1;
        *str_cpy = *str_cpy + 1;
    }
}

static void count_strs(char ***str_cpy, size_t *old_len)
{
    while (**str_cpy)
    {
        *old_len = *old_len + 1;
        *str_cpy = *str_cpy + 1;
    }
}

void add_to_2d(char ***src, t_tok *tok)
{
    char **str;
    char **str_cpy;
    char **new_str;
    char **new_str_cpy;
    size_t old_len;

    str = *src;
    if (str == NULL)
    {
        str = malloc(sizeof(char *) * 1);
        str[0] = NULL;
    }
    old_len = 0;
    str_cpy = str;
    count_strs(&str_cpy, &old_len);
    new_str = malloc(sizeof(char *) * (old_len + 2));
    new_str_cpy = new_str;
    str_cpy = str;
    cpy_old_data(&str_cpy, &new_str_cpy);
    *new_str_cpy = ft_strdup(tok->data);
    new_str_cpy++;
    *new_str_cpy = NULL;
    free(str);
    *src = new_str;
}
