#include "parse.h"

static int	check_len(int str_len, char *src, char *dst)
{
	if (str_len <= 1)
	{
		ft_strlcpy(dst, src, str_len);
		return (-1);
	}
	return (0);
}

void		strip_quotes(char *src, char *dst)
{
	char	quote;
	int		str_len;
	char	c;
	int		i;
	int		j;

	str_len = ft_strlen(src);
	if (check_len(str_len, src, dst) != 0)
		return ;
	quote = 0;
	i = 0;
	j = 0;
	while (i < str_len)
	{
		c = src[i];
		if ((c == '\'' || c == '\"') && quote == 0)
			quote = c;
		else if (c == quote)
			quote = 0;
		else
			dst[j++] = c;
		i++;
	}
	dst[j] = 0;
}
