#include <signal.h>

int	main(int ac, char **av)
{
	raise(SIGSEGV);
}
