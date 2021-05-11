#include "../../minishell.h"

static void if_general(char **str, int *state)
{
    if (**str == '\\' && *(*str + 1) != '\0')
        *str = *str + 1;
    else if (**str == '\'')
        *state = STATE_IN_QUOTE;
    else if (**str == '\"')
        *state = STATE_IN_DQUOTE;
}

int validate_quotation(char *str)
{
    int state;

    state = STATE_GENERAL;
    while (*str)
    {
        if (state == STATE_GENERAL)
            if_general(&str, &state);
        else if (state == STATE_IN_QUOTE && *str == '\'')
                state = STATE_GENERAL;
        else if (state == STATE_IN_DQUOTE)
        {
            if (*str == '\\' && *(str + 1) != '\0')
                str++;
            else if (*str == '\"')
                state = STATE_GENERAL;
        }
        if (*str != '\0')
            str++;
    }
    if (state != STATE_GENERAL)
        return (-1);
    return (0);
}
