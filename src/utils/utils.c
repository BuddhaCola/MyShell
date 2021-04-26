#include "../minishell.h"

void i_want_to_be_freed(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}