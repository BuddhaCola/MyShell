/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igearhea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 18:51:42 by igearhea          #+#    #+#             */
/*   Updated: 2020/11/07 18:51:45 by igearhea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*set_s(int n, int count)
{
	char	*ptr;
	char	*save_ptr;
	int		target;
	int		sign;

	sign = 1;
	target = 0;
	ptr = malloc(sizeof(char) * count + 1);
	if (!ptr)
		return (ptr);
	save_ptr = ptr;
	ptr[count] = '\0';
	if (n < 0)
	{
		ptr[0] = '-';
		target = 1;
		sign = -1;
	}
	while (count-- != target)
	{
		ptr[count] = sign * (n % 10) + '0';
		n /= 10;
	}
	return (save_ptr);
}

static int		do_count(int n)
{
	int		count;

	count = 0;
	if (n <= 0)
		count++;
	while (n)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char			*ft_itoa(int n)
{
	char	*ptr;

	ptr = set_s(n, do_count(n));
	return (ptr);
}
