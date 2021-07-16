/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deref_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igearhea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 17:04:55 by igearhea          #+#    #+#             */
/*   Updated: 2021/05/13 17:04:56 by igearhea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*search_key(t_todo *all, char *key)
{
	char	*ret;

	ret = env_get_value(all, key);
	if (ret == NULL)
		return (NULL);
	return (ft_strdup(ret));
}

char	*put_nothing(char *src, char *start, char **stop)
{
	char	*ret;
	int		i;
	int		len_for_start;

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

static void	while_answer_do(char **answer, char	**ret, int *i)
{
	while (**answer)
	{
		if (**answer == '\'' || **answer == '\"' || **answer == '\\'
			|| **answer == '|' || **answer == '>' || **answer == '<')
		{
			(*ret)[(*i)++] = '\\';
			(*ret)[(*i)++] = **answer;
			*answer = *answer + 1;
		}
		else
		{
			(*ret)[(*i)++] = **answer;
			*answer = *answer + 1;
		}
	}
}

char	*put_answer(char *src, char *start, char **stop, char *answer)
{
	char	*ret;
	int		i;
	int		len_for_start;

	ret = malloc(sizeof(char) * (ft_strlen(src) + ft_strlen(answer)
				* 2 + 1));
	i = 0;
	len_for_start = start - src;
	while (i < (len_for_start))
		ret[i++] = *src++;
	while_answer_do(&answer, &ret, &i);
	src += *stop - src;
	*stop = &(ret[i - 1]);
	while (*src)
		ret[i++] = *src++;
	ret[i] = '\0';
	return (ret);
}

void	get_key(t_todo *all)
{
	all->d_u.start = (all->d_u.str)++;
	all->d_u.key_iter = 0;
	while (*(all->d_u.str) && (ft_isalpha(*(all->d_u.str))
			   || ft_isdigit(*(all->d_u.str))
			   || *(all->d_u.str) == '_'
			   || *(all->d_u.str) == '?'))
		all->d_u.key[(all->d_u.key_iter)++] = *(all->d_u.str++);
	all->d_u.key[all->d_u.key_iter] = '\0';
	all->d_u.answer = search_key(all, all->d_u.key);
	if (all->d_u.answer != NULL && all->d_u.key_iter != 0)
	{
		all->d_u.new_src = put_answer(*(all->d_u.src),
				all->d_u.start, &(all->d_u.str), all->d_u.answer);
		free(*(all->d_u.src));
		*(all->d_u.src) = all->d_u.new_src;
		free(all->d_u.answer);
	}
	else if (all->d_u.answer == NULL && all->d_u.key_iter != 0)
	{
		all->d_u.new_src = put_nothing(*(all->d_u.src),
				all->d_u.start, &(all->d_u.str));
		free(*(all->d_u.src));
		*(all->d_u.src) = all->d_u.new_src;
	}
}
