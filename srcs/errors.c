#include "minishell.h"

void	error(int err_code)
{
	write(2, PROMPT, ft_strlen(PROMPT));
	if (err_code == ER_MALLOC)
		perror(": malloc");
	if (err_code == ER_EXECVE)
		perror(": execve");
	if (err_code == ER_GETCWD)
		perror(": getcwd");
	if (err_code == ER_CHDIR)
		perror(": chdir");
	if (err_code == ER_FORK)
		perror(": fork");
	if (err_code == ER_ACCESS)
		perror(": access");
	if (err_code == ER_DIR)
		perror(": opendir");
	if (err_code == ER_OPEN)
		perror(": open");
	if (err_code == ER_DUP)
		perror(": dup2");
	if (err_code == ER_CDMINUS)
		write(2, ": cd: OLDPWD not set\n", 21);
	exit(0);
}
