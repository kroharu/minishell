#include "minishell.h"

void	error_exit(int cmd)
{
	int	err_code;

	err_code = errno;
	write(2, "💩", ft_strlen("💩"));
	if (cmd == ER_MALLOC)
		perror(": malloc");
	if (cmd == ER_FORK)
		perror(": fork");
	if (cmd == ER_DUP)
		perror(": dup2");
	if (cmd == ER_UNLINK)
		perror(": unlink");
	free_all(g_info);
	exit(err_code);
}

void	error(int err_code)
{
	write(2, "💩", ft_strlen("💩"));
	if (err_code == ER_EXECVE)
		perror(": execve");
	if (err_code == ER_GETCWD)
		perror(": getcwd");
	if (err_code == ER_CHDIR)
		perror(": chdir");
	if (err_code == ER_ACCESS)
		perror(": access");
	if (err_code == ER_DIR)
		perror(": opendir");
	if (err_code == ER_OPEN)
		perror(": open");
	if (err_code == ER_CDMINUS)
		write(2, ": cd: OLDPWD not set\n", 21);
	/*if (err_code == ER_MALLOC)*/
		/*perror(": malloc");*/
	/*if (err_code == ER_FORK)*/
		/*perror(": fork");*/
	/*if (err_code == ER_DUP)*/
		/*perror(": dup2");*/
	exit(err_code);
	/*return (errno);*/
}
