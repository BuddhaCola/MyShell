/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtaylor <wtaylor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 18:15:43 by wtaylor           #+#    #+#             */
/*   Updated: 2021/04/12 14:54:44 by wtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void test_parse(char *buf, t_todo *all)
{
	int i = -1;
	while (buf[++i])
	{
		if (buf[i] == '$')
		{
			i++;
			char *envp;
			if (!(envp = ft_dollarsign(&buf[i], all)))
				envp = "";
			printf("%s\n", envp);
		}
		else if (buf[i] == '!')
			exec_bin(&buf[i+1], all);
		else if (buf[i] == '?')
			printf("%d\n", all->exec.err);
		else if (buf[i] == '|')
		{
			char **args = ft_split(&buf[i+1], ' ');
			ft_pipe(args[0], 0, args[1], 0);
		}
		else if (buf[i] == '>')
			redirection("./test", "/bin/cat", 0, 2);
		else if (buf[i] == 'x')
			ft_export(all, 0);
		else if (buf[i] == 'e')
			ft_env(all);
	}
	free(buf);
}

int		shell(t_todo *all)
{
	char	*buf;
	handle_signals();
	while (1)
	{
		ft_putstr_fd(PROMT, 1);
		get_next_line(0, &buf);
		test_parse(buf, all);
	}
	return (0);
}

int		main(int argc, char **argv, char **env)
{
	t_todo		all;

	collect_env(&all, env);
//	ft_export(&all, 0);
//	shell(&all);
	return (0);
}