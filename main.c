#include "minishell.h"

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
	printf("minishell$ ");
	// parse(argc, argv);
	// printenv(env);
	return (0);
}