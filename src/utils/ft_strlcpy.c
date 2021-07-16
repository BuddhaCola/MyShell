/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtaylor <wtaylor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 17:20:13 by wtaylor           #+#    #+#             */
/*   Updated: 2020/11/10 13:56:04 by wtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dsize)
{
	const char	*s;
	size_t		n;

	s = src;
	n = dsize;
	if (!dst || !src)
		return (0);
	if (dsize)
	{
		while (--n)
		{
			*dst = *src++;
			if (*dst++ == '\0')
				break ;
		}
	}
	if (n == 0)
	{
		if (dsize)
			*dst = '\0';
		while (*src)
			src++;
		src++;
	}
	return (src - s - 1);
}
