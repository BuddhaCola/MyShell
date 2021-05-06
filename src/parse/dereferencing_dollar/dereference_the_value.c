#include "../../minishell.h"

static char *escape_special_characters(char *src_str)
{
	char *str;
	str = malloc(sizeof(char) * (ft_strlen(src_str) * 2) + 1);
	while (*src_str)
	{
		//if symbol do escape else just copy
		*src_str++;
	}
	return (str);
}

static char *search_key(char *key)
{

}

static char *put_answer()
{

}

static char *put_nothing()
{

}

static void try_dereference(char **src)
{
	char *str;
	size_t i;
	char *key;
	char *k;
	int k_iter;
	//state mashine
	int state;
	int state_general;
	int state_q;
	int state_dq;
	state_general = 0;
	state_q = 1;
	state_dq = 2;


	str = *src;
	i = 0;
	k_iter = 0;
	state = state_general;
	key = malloc (sizeof(char) * ft_strlen(str) + 1);
	while (*str)
	{
		if (state == state_general)
		{
			if (*str == '\\')
			{
				if (*(str + 1) == '\0' || *(str + 2) == '\0')
					break;
				str += 2;
				continue;
			}
			if (*str == '$')
			{
				if (*(str + 1) == '\0')
					break;
				if (ft_isalpha(*(str + 1)))
				{
					k = str + 1;
					//here i is on '$' position in str
					while (*k && (ft_isalpha(*k) || ft_isdigit(*k) || *k == '_'))
					{
						key[k_iter] = *k;
						k_iter++;
						k++;
					}
					key[k_iter] = '\0';
					//do not touch $ if he is alone, write answer from key if exist, and write NOTHING if key doesnt exists
					if (k = 0)
						continue;
					//search key for answer
					if (search_key(key) != NULL)
					{
						//put answer
						put_answer();
					}
					else
					{
						//put ""
						put_nothing();
					}
				}
			}
			if (*str == '\'')
				state = state_q;
			if (*str == '\"')
				state = state_dq;
		}
		else if (state == state_q)
		{
			if (*str == '\'')
				state = state_general;
		}
		else if (state == state_dq)
		{
			if (*str == '\\')
			{
				if (*(str + 1) == '\0' || *(str + 2) == '\0')
					break;
				str += 2;
				continue;
			}
			if (*str == '$')
			{

			}
			if (*str == '\"')
				state = state_general;
		}

		i++;
		str++;
	}
	free(key);
}

void dereference_the_value(t_todo *all)
{
	t_pipelist *pipe_elem;
	t_tok *token;

	pipe_elem = all->parse_utils->pipelist;
	token = pipe_elem->tok_lst;
	//for every token try_dereference
	while (pipe_elem != NULL)
	{
		while (token != NULL)
		{
			try_dereference(&(token->data));
			token = token->next;
		}
		pipe_elem = pipe_elem->next;
		token = pipe_elem->tok_lst;
	}
}
