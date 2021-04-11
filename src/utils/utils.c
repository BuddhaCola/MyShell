#include "../minishell.h"

size_t	ft_strlcat(char *dst, char *src, size_t dsize)
{
	char	*d;
	char	*s;
	size_t		n;
	size_t		dlen;

	d = dst;
	s = src;
	n = dsize;
	while (n-- && *dst)
		dst++;
	dlen = dst - d;
	n = dsize - dlen;
	if (n-- == 0)
		return (dlen + ft_strlen(src));
	while (*src)
	{
		if (n)
		{
			*dst++ = *src;
			n--;
		}
		src++;
	}
	*dst = '\0';
	return (dlen + (src - s));
}

size_t		ft_strlen(char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*p;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!(p = malloc(len * sizeof(char))))
		return (NULL);
	ft_strlcat(p, s1, len);
	ft_strlcat(p, s2, len + 1);
	return (p);
}