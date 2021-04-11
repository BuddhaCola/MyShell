#include "minishell.h"

/*
SOME CHANGES BY RAFAEL IN LINE 3,4,5
adadadasda
*/
void	printenv(char **env)
{
	int i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}



int		main(int argc, char **argv, char **env)
{
	write(1, "minishell 👉 ", 15);
	// parse(argc, argv);
	// printenv(env);
	return (0);
}