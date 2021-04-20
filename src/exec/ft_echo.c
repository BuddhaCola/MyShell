/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtaylor <wtaylor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 13:39:20 by wtaylor           #+#    #+#             */
/*   Updated: 2021/04/12 17:21:58 by wtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int 	ft_echo(int argc, char **argv)
{
	char	endsymbol;
	int		i;

	endsymbol = '\n';
	if (argc > 1)
	{
		i = 1;
		if (!(ft_strncmp(argv[1], "-n", 3)))
		{
			endsymbol = 0;
			i++;
		}
		while (i < argc)
		{
			write(1, argv[i], ft_strlen(argv[i]));
			i++;
			if (i != argc)
				write(1, " ", 1);
		}
	}
	write(1, &endsymbol, 1);
	return (0);
}
