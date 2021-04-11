#include "minishell.h"

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *org, char *append)
{
	int		len1;
	int		len2;
	char	*newline;

	len1 = ft_strlen(org);
	len2 = ft_strlen(append);
	newline = malloc(sizeof(char) * (len1 + len2 + 1));
	newline[len1 + len2] = '\0';
	while (len2-- >= 0)
		newline[len1 + len2] = append[len2];
	while (--len1 >= 0)
		newline[len1] = org[len1];
	return(newline);
}