#include <signal.h>

int	main(int ac, char **av)
{
	free(av[0]);
	//raise(SIGPIPE);
}
