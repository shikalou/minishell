#include "minishell.h"

int	main()
{
	char *cmd;

	cmd = readline("nelson et zor minishell$ ");
	printf("%s\n", cmd);
	return (0);
}