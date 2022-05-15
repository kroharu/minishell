#include "minishell.h"

void	error(int err_code)
{
	write(1, PROMPT, ft_strlen(PROMPT));
	if (err_code == ER_MALLOC)
		perror("minishell: malloc");
	if (err_code == ER_EXECVE)
		perror("minishell: execve");
	if (err_code == ER_GETCWD)
		perror("minishell: getcwd");
	if (err_code == ER_CHDIR)
		perror("minishell: chdir");
	if (err_code == ER_FORK)
		perror("minishell: fork");
	if (err_code == ER_ACCESS)
		perror("minishell: access");
	if (err_code == ER_DIR)
		perror("minishell: opendir");
	if (err_code == ER_OPEN)
		perror("minishell: open");
	if (err_code == ER_DUP)
		perror("minishell: dup2");
	exit(0);
}
