/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igearhea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 01:41:20 by igearhea          #+#    #+#             */
/*   Updated: 2020/11/07 16:57:29 by igearhea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	exit_free(char **ptr)
{
	char	**save_ptr;

	save_ptr = ptr;
	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free(save_ptr);
}

static int	set_words(char **ptr, char const *s, char c)
{
	char	*start;
	char	*end;
	char	*save_s;

	save_s = (char *)s;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s != c && *s != '\0')
		{
			start = (char *)s;
			while (*s != c && *s != '\0')
				s++;
			end = (char *)s - 1;
			*ptr = ft_substr(save_s, start - save_s, end - start + 1);
			if (*ptr == 0)
				return (1);
			ptr++;
		}
	}
	*ptr = 0;
	return (0);
}

size_t		count_words(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s != c && *s != '\0')
			count++;
		while (*s != c && *s != '\0')
			s++;
	}
	return (count);
}

char		**ft_split(char const *s, char c)
{
	char	**ptr;
	size_t	word_number;
	size_t	succesfull_allocs;

	if (!s)
		return (0);
	word_number = count_words(s, c);
	succesfull_allocs = 0;
	ptr = (char **)malloc((word_number + 1) * sizeof(char *));
	if (!ptr)
		return (0);
	if (set_words(ptr, s, c))
	{
		exit_free(ptr);
		return (0);
	}
	return (ptr);
}
