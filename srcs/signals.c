#include "minishell.h"

void	quit_handler_child(int signum)
{
	if (signum == SIGQUIT)
		exit(131);
}

void	sigint_empty_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n"); // Move to a new line
		rl_on_new_line(); // Regenerate the prompt on a newline
		rl_replace_line("", 0); // Clear the previous text
		rl_redisplay();
	}
}

void	sigint_handler(int signum)
{
	(void)signum;
	printf("SIGINT\n");//сделать глобальную структуру и тестить с ней
	exit(0);
}
