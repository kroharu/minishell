#include "minishell.h"

void	error_exit(int code, char *cmd)
{
	int	err_code;

	err_code = errno;
	write(STDERR_FILENO, "💩: ", ft_strlen("💩: "));
	if (code == ER_MALLOC)
		perror("malloc");
	if (code == ER_FORK)
		perror("fork");
	if (code == ER_DUP)
		perror("dup2");
	if (code == ER_CMDDIR)
	{
		write(STDERR_FILENO, cmd, ft_strlen(cmd));
		write(STDERR_FILENO, ": is a directory\n", 17);
	}
	free_all(g_info);
	exit(err_code);
}

void	error(int err_code, char *cmd, char *input)
{
	g_info->status = errno;
	write(STDERR_FILENO, "💩: ", ft_strlen("💩: "));
	/*if (err_code == ER_GETCWD)*/
		/*perror("getcwd");*/
	/*if (err_code == ER_CHDIR)*/
		/*perror("chdir");*/
	/*if (err_code == ER_ACCESS)*/
		/*perror("access");*/
	/*if (err_code == ER_DIR)*/
		/*perror("opendir");*/
	/*if (err_code == ER_OPEN)*/
		/*perror("open");*/
	/*if (err_code == ER_UNLINK)*/
		/*perror("unlink");*/
	/*if (err_code == ER_EXECVE)*/
		/*perror("execve");*/
	if (err_code == ER_CDMINUS)
		write(STDERR_FILENO, "cd: OLDPWD not set\n", 19);
	else if (err_code == ER_CMDNOTFND)
	{
		write(STDERR_FILENO, cmd, ft_strlen(cmd));
		write(STDERR_FILENO, ": command not found\n", 20);
		g_info->status = 127;
	}
	else
	{
		write(STDERR_FILENO, cmd, ft_strlen(cmd));
		write(STDERR_FILENO, ": ", 2);
		perror(input);
	}
}
