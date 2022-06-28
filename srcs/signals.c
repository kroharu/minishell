#include "minishell.h"

void	sigquit_handler_child(int signum)
{
	if (signum == SIGQUIT)
		exit(131);
}

void	sigint_empty_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("%s \b\b    \n", PROMPT); // Move to a new line
		rl_on_new_line(); // Regenerate the prompt on a newline
		rl_replace_line("", 0); // Clear the previous text
		rl_redisplay();
	}
}

void	sigint_handler_parent(int signum)
{
	if (signum == SIGINT)
	{
		signal(SIGINT, SIG_IGN);
		kill(0, SIGINT);
		/*if (g_info->last_flag)*/
			write(1, "\n", 1);
	}
}

void	sigquit_handler_parent(int signum)
{
	if (signum == SIGQUIT)
	{
		signal(SIGQUIT, SIG_IGN);
		kill(0, SIGQUIT);
		/*if (g_info->last_flag)*/
			write(1, "Quit: 3\n", 9);
		/*g_info->last_flag = 0;*/
	}
}
