#include "minishell.h"

int	ft_parsing(char *cmd)
{
	char	**splitted;

	splitted = ft_split(cmd, ' ');
	printf("%s\n", splitted[0]);
	return (0);
}


int	main()
{
	char *cmd;
	while (1)
	{
		cmd = readline("nelson et zor minishell$ ");
		printf("%s\n", cmd);
		ft_parsing(cmd);
	}
	return (0);
}
