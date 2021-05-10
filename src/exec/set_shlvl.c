#include "../minishell.h"

int	numlen(char *str)
{
	int	len;

	len = 0;
	while (ft_isdigit(str[len]))
		len++;
	return (len);
}

int	shlvl_validation(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (i == 1)
			return (1);
		if (ft_strchr("0123456789-+", *str))
		{
			if (ft_isdigit(*str) && !ft_isdigit(*(str + 1)))
			{
				if (numlen(str) > 3)
					return (1);
				i++;
			}
			str++;
		}
		else
			return (1);
	}
	return (0);
}

void	set_shlvl(t_todo *all)
{
	char	**shlvl;
	int		oldlvl;

	shlvl = env_search(all->environments, "SHLVL");
	if (shlvl)
	{
		if (shlvl_validation(ft_strchr(*shlvl, '=') + 1))
			env_set_value(all, "SHLVL", "0");
		else
		{
			oldlvl = ft_atoi(ft_strchr(*shlvl, '=') + 1);
			if (oldlvl < 0)
				env_set_value(all, "SHLVL", "-1");
			else if (oldlvl >= 999 || (numlen(ft_strchr(*shlvl, '=')) > 3))
			{
				ft_putstr_fd("bash: warning: shell level (", 1);
				ft_putstr_fd(ft_strchr(*shlvl, '=') + 1, 1);
				ft_putstr_fd(") too high, resetting to 1\n", 1);
				env_set_value(all, "SHLVL", "0");
			}
		}
	}
	env_update(all, "SHLVL", 0, '+');
}
