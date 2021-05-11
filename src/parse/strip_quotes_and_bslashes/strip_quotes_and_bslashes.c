#include "../../minishell.h"

/*
 * смысол этой функции это: создать строку на основе заданной и удалить не
 * нужные кавычки плюс удалить backslasehes. Удаляет старый.
 */
//void strip_quotes_and_bslashes(char **src)
//{
//	char *str;
//	char *new_str;
//	char *ret;
//	int state;
//
//	str = *src;
//	new_str = malloc(sizeof(char) * ft_strlen(*src) + 1);
//	ret = new_str;
//	state = STATE_GENERAL;
//	while (*str)
//	{
//		if (state == STATE_GENERAL)
//		{
//			if (*str == '\\')
//			{
//				str++;
//				*new_str++ = *str;
//			}
//			else if (*str == '\'')
//				state = STATE_IN_QUOTE;
//			else if (*str == '\"')
//				state = STATE_IN_DQUOTE;
//			else
//				*new_str++ = *str;
//		}
//		/////^^^^
//		else if (state == STATE_IN_QUOTE)
//		{
//			if (*str == '\'')
//				state = STATE_GENERAL;
//			else
//				*new_str++ = *str;
//		}
//		else if (state == STATE_IN_DQUOTE)
//		{
//			if (*str == '\\')
//			{
//				str++;
//				*new_str++ = *str;
//			}
//			else if (*str == '\"')
//				state = STATE_GENERAL;
//			else
//				*new_str++ = *str;
//		}
//		str++;
//	}
//	*new_str = '\0';
//
//	//end
//	free(*src);
//	*src = ret;
//}

static void if_general(int *state, char **str, char **new_str)
{
	if (**str == '\\')
	{
		*str = *str + 1;
		**new_str = **str;
		*new_str = *new_str + 1;
	}
	else if (**str == '\'')
		*state = STATE_IN_QUOTE;
	else if (**str == '\"')
		*state = STATE_IN_DQUOTE;
	else
	{
		**new_str = **str;
		*new_str = *new_str + 1;
	}
}

static void if_quote(int *state, char **str, char **new_str)
{
	if (**str == '\'')
		*state = STATE_GENERAL;
	else
	{
		**new_str = **str;
		*new_str = *new_str + 1;
	}
}

static void if_dquote(int *state, char **str, char **new_str)
{
	if (**str == '\\')
	{
		*str = *str + 1;
		**new_str = **str;
		*new_str = *new_str + 1;
	}
	else if (**str == '\"')
		*state = STATE_GENERAL;
	else
	{
		**new_str = **str;
		*new_str = *new_str + 1;
	}
}

void strip_quotes_and_bslashes(char **src)
{
	char *str;
	char *new_str;
	char *ret;
	int state;

	str = *src;
	new_str = malloc(sizeof(char) * ft_strlen(*src) + 1);
	ret = new_str;
	state = STATE_GENERAL;
	while (*str)
	{
		if (state == STATE_GENERAL)
			if_general(&state, &str, &new_str);
		else if (state == STATE_IN_QUOTE)
			if_quote(&state, &str, &new_str);
		else if (state == STATE_IN_DQUOTE)
			if_dquote(&state, &str, &new_str);
		str++;
	}
	*new_str = '\0';
	free(*src);
	*src = ret;
}
