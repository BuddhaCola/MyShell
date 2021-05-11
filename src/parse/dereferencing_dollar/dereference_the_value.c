#include "../../minishell.h"

//allocates answer if exist
static char *search_key(t_todo *all, char *key)
{
	char *ret;

	ret = env_get_value(all, key);
	if (ret == NULL)
		return NULL;
	return (ft_strdup(ret));
}

//allocates tokens str with modefying it 
static char *put_nothing(char *src, char *start, char **stop)
{
	char *ret;
	int i;
	int len_for_start;

	ret = malloc(sizeof(char) * (ft_strlen(src) + 1));
	i = 0;
	len_for_start = start - src;
	while (i < (len_for_start))
		ret[i++] = *src++;
	src += *stop - src;
	if (i != 0)
		*stop = &(ret[i - 1]);
	else
		*stop = ret;
	while (*src)
		ret[i++] = *src++;
	ret[i] = '\0';
	return (ret);
}

//allocates tokens str with dereferenced string
static char *put_answer(char *src, char *start, char **stop, char *answer)
{
	char *ret;
	int i;
	int len_for_start;

	ret = malloc(sizeof(char) * (ft_strlen(src) + ft_strlen(answer)
			* 2 + 1));
	//cpy to start		from src
	i = 0;
	len_for_start = start - src;
	while (i < (len_for_start))
		ret[i++] = *src++;
	//cpy answer
	while (*answer)
	{
		if (*answer == '\'' || *answer == '\"' || *answer == '\\'
			|| *answer == '|' || *answer == '>' || *answer == '<')
		{
			ret[i++] = '\\';
			ret[i++] = *answer++;
		}
		else
			ret[i++] = *answer++;
	}
	//set new *stop pos
	src += *stop - src;
	*stop = &(ret[i - 1]);
	//cpy after answer	from src
	while (*src)
		ret[i++] = *src++;
	//nool terminate ret
	ret[i] = '\0';
	//ret result
	return (ret);
}

static void try_dereference(t_todo *all, char **src)
{
	char *str;
	char *start;
	char *key;
	char *answer;
	char *new_src;
	int key_iter;
	int state;

	state = STATE_GENERAL;
	str = *src;
	key = malloc (sizeof(char) * ft_strlen(str) + 1);
	while (*str)
	{
		if (state == STATE_GENERAL)
		{
			if (*str == '\\')
			{
				if (*(str + 1) == '\0' || *(str + 2) == '\0')
					break;
				str++;
			}
			else if (*str == '$' && *(str + 1) != '\0'
			&& (ft_isalpha(*(str + 1)) || ft_strchr("?_", *(str + 1))))
			{
				start = str++;
				key_iter = 0;
				while (*str && (ft_isalpha(*str) || ft_isdigit(*str)
				|| *str == '_' || *str == '?'))
					key[key_iter++] = *str++;
				key[key_iter] = '\0';
				answer = search_key(all, key);
				if (answer != NULL && key_iter != 0)
				{
					//put answer, refresh src, str must be at the (and - 1)
					//of answer in the src.
					new_src = put_answer(*src, start, &str, answer);
					free(*src);
					*src = new_src;
					free(answer);
				}
				else if (answer == NULL && key_iter != 0)
				{
					//put "", refresh src, str must be at the (and - 1)
					//of answer in the src.
					new_src = put_nothing(*src, start, &str);
					free(*src);
					*src = new_src;
				}
			}
			else if (*str == '\'')
				state = STATE_IN_QUOTE;
			else if (*str == '\"')
				state = STATE_IN_DQUOTE;
		}
		else if (state == STATE_IN_QUOTE && *str == '\'')
				state = STATE_GENERAL;
		else if (state == STATE_IN_DQUOTE)
		{
			if (*str == '\\')
			{
				if (*(str + 1) == '\0' || *(str + 2) == '\0')
					break;
				str++;
			}
			else if (*str == '$' && *(str + 1) != '\0'
					 && (ft_isalpha(*(str + 1)) || ft_strchr("?_", *(str + 1))))
			{
				start = str++;
				key_iter = 0;
				while (*str && (ft_isalpha(*str) || ft_isdigit(*str)
								|| ft_strchr("?_", *(str))))
					key[key_iter++] = *str++;
				key[key_iter] = '\0';
				answer = search_key(all, key);
				if (answer != NULL && key_iter != 0)
				{
					//put answer, refresh src, str must be at the (and - 1)
					//of answer in the src.
					new_src = put_answer(*src, start, &str, answer);
					free(*src);
					*src = new_src;
					free(answer);
				}
				else if (answer == NULL && key_iter != 0)
				{
					//put "", refresh src, str must be at the (and - 1)
					//of answer in the src.
					new_src = put_nothing(*src, start, &str);
					free(*src);
					*src = new_src;
				}
			}
			else if (*str == '\"')
				state = STATE_GENERAL;
		}
		str++;
	}
	free(key);
}

//static void init(int *state, char **str, char **src, char **key)
//{
//    *state = STATE_GENERAL;
//    *str = *src;
//    *key = malloc (sizeof(char) * ft_strlen(*str) + 1);
//}
////                              /
//static void work_with_key(t_todo *all, char **str, char **key, char ***src)
//{
//    char *start;
//    char *answer;
//    char *new_src;
//    int key_iter;
//
//    start = *str++;
//    key_iter = 0;
//    while (**str && (ft_isalpha(**str) || ft_isdigit(**str)
//                    || **str == '_' || **str == '?'))
//        (*key)[key_iter++] = *(*str++);
//    (*key)[key_iter] = '\0';
//    answer = search_key(all, *key);
//    if (answer != NULL && key_iter != 0)
//    {
//        //put answer, refresh src, str must be at the (and - 1)
//        //of answer in the src.
//        new_src = put_answer(**src, start, &(*str), answer);
//        free(*src);
//        **src = new_src;
//        free(answer);
//    }
//    else if (answer == NULL && key_iter != 0)
//    {
//        //put "", refresh src, str must be at the (and - 1)
//        //of answer in the src.
//        new_src = put_nothing(**src, start, &(*str));
//        free(*src);
//        **src = new_src;
//    }
//}
//
//static void try_dereference(t_todo *all, char **src)
//{
//    int state;
//    char *str;
//    char *key;
//
//    init(&state, &str, src, &key);
//    while (*str)
//    {
//        if (state == STATE_GENERAL)
//        {
//            if (*str == '\\')
//                    str++;
//            else if (*str == '$' && *(str + 1) != '\0'
//                     && (ft_isalpha(*(str + 1)) || ft_strchr("?_", *(str + 1))))
//                work_with_key(all, &str, &key, &src);
//            else if (*str == '\'')
//                state = STATE_IN_QUOTE;
//            else if (*str == '\"')
//                state = STATE_IN_DQUOTE;
//        }
//        else if (state == STATE_IN_QUOTE && *str == '\'')
//            state = STATE_GENERAL;
//        else if (state == STATE_IN_DQUOTE)
//        {
//            if (*str == '\\')
//                str++;
//            else if (*str == '$' && *(str + 1) != '\0'
//                     && (ft_isalpha(*(str + 1)) || ft_strchr("?_", *(str + 1))))
//                work_with_key(all, &str, &key, &src);
//            else if (*str == '\"')
//                state = STATE_GENERAL;
//        }
//        if (*str != '\0')
//            str++;
//    }
//    free(key);
//}
















































void dereference_the_value(t_todo *all)
{
	t_pipelist *pipe_elem;
	t_tok *token;

	pipe_elem = all->parse_utils->pipelist;
	//for every token try_dereference
	while (pipe_elem != NULL)
	{
		token = pipe_elem->tok_lst;
		while (token != NULL)
		{
			if (token->type == TOKEN)
				try_dereference(all, &(token->data));
			token = token->next;
		}
		pipe_elem = pipe_elem->next;
	}
}
