#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

typedef	struct {

}		todo;

size_t	ft_strlen(char *str);
char	*ft_strjoin(char *org, char *append);
size_t	ft_strlcat(char *dst, char *src, size_t dsize);

// builtins
void	ft_pwd();