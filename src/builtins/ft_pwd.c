/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtaylor <wtaylor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 17:59:47 by wtaylor           #+#    #+#             */
/*   Updated: 2021/04/11 20:58:12 by wtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd()
{
		char	*pwd;
		size_t	len;

		pwd = NULL;
		getcwd(pwd, len);
		printf("pwd:%s\n", pwd);
}

int main(int ac, char **av, char **env)
{
	ft_pwd();
}