#include "minishell.h"

void	error(int err_code)
{
	if (err_code == ER_MALLOC)
		perror(" malloc");
	if (err_code == ER_EXECVE)
		perror(" execve");
	if (err_code == ER_GETCWD)
		perror(" getcwd");
	exit(0);
}
