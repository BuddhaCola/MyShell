#include "../../minishell.h"

/*
 * смысол этой функции это: создать строку на основе заданной и удалить не
 * нужные кавычки плюс удалить backslasehes.
 */
void strip_quotes_and_bslashes(char **src)
{
	char *str;
	char *new_str;
	int state;

	str = *src;
	new_str = malloc(sizeof(char) * ft_strlen(*src));
	state = STATE_GENERAL;
	while (*str)
	{
		if (state == STATE_GENERAL)
		{
			if (1)
			{

			}
			else if (*str == '\'')
				state = STATE_IN_QUOTE;
			else if (*str == '\"')
				state = STATE_IN_DQUOTE;
		}
		else if (state == STATE_IN_QUOTE)
		{
			if (*str == '\'')
				state = STATE_GENERAL;
		}
		else if (state == STATE_IN_DQUOTE)
		{
			if (*str == '\"')
				state = STATE_GENERAL;
		}
		str++;
	}

	//end
	free(*src);
	*src = new_str;
}
