#include "minishell.h"

void	quit_handler_child(int signum)
{
	if (signum == SIGQUIT)
		exit(131);
}

void	sigint_handler(int signum)
{
	(void)signum;
	printf("SIGINT\n");//сделать глобальную структуру и тестить с ней
	exit(0);
}
