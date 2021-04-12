/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtaylor <wtaylor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 13:39:20 by wtaylor           #+#    #+#             */
/*   Updated: 2021/04/12 14:54:42 by wtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	if (!*needle)
		return ((char *)haystack);
	if (!len)
		return (NULL);
	i = 0;
	while (haystack[i] && i < len)
	{
		j = 0;
		if (haystack[i] == needle[j])
		{
			while (i + j < len && haystack[i + j] == needle[j])
			{
				j++;
				if (!needle[j])
					return ((char *)&haystack[i]);
			}
		}
		i++;
	}
	return (NULL);
}

char	*ft_envpsearch(const char *haystack, const char *needle)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(needle);
	while(i < len - 1)
	{
		if (needle[i] == haystack[i])
				i++;
		else
			return (NULL);
	}
	if (haystack[i+1] == '=')
	{
		i+= 2;
		return(ft_strdup(&haystack[i]));
	}
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