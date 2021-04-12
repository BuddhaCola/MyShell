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

char	*ft_envpsearch(const char *haystack, const char *needle)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(needle);

	while(i < len && needle[i])
	{
		if (needle[i] == haystack[i])
				i++;
		else
			return (NULL);
	}
	if (haystack[i] == '=')
		return(ft_strdup(&haystack[++i]));
	return (NULL);
}

char	*ft_dollarsign(char	*str, t_todo *all)
{
	int		i;
	int		len;
	char	*envp;

	i = 0;
	if (!*str || !(len = ft_strlen(str)) || *str < 33 || *str > 126)
		return("$");
	while (all->exec.env[i])
	{
		if ((envp = ft_envpsearch(all->exec.env[i], str)))
			return (envp);
		i++;
	}
	return(NULL);
}