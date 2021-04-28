#include "../../../minishell.h"

static char *get_new_str(size_t size)
{
    char *ptr;
    if (size < 1)
        return (NULL);
    ptr = malloc(sizeof(char) * size + 1);
    ptr[size] = '\0';
    return (ptr);
}

void    strip_quotes(char **dst, char *src)
{
    size_t  src_len;
    size_t  i;
    size_t  j;
    char    *str;
    char    flg;

    src_len = ft_strlen(src);
    if (src_len < 1)
        return ;
    str = get_new_str(src_len);
    i = 0;
    j = 0;
    flg = 0;
    while (src[i])
    {
        if ((src[i] == '\'' || src[i] == '\"') && flg == 0)
            flg = src[i];
        else if (src[i] == flg)
            flg = 0;
        else
            str[j++] = src[i];
        i++;
    }
    str[j] = '\0';
    *dst = str;
}
