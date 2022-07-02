#include "minishell.h"

void	error_exit(int code, char *cmd)
{
	int	err_code;

	err_code = errno;
	write(STDERR_FILENO, PROMPT_ERR, ft_strlen(PROMPT_ERR));
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

void	error(int err_code, char *cmd, char *input, char *text)
{
	write(STDERR_FILENO, PROMPT_ERR, ft_strlen(PROMPT_ERR));
	if (text)
	{
		g_info->status = 1;
		write(STDERR_FILENO, cmd, ft_strlen(cmd));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, input, ft_strlen(input));
		write(STDERR_FILENO, text, ft_strlen(text));
	}
	/*else if (err_code == ER_CMDNOTFND)*/
	/*{*/
		/*write(STDERR_FILENO, cmd, ft_strlen(cmd));*/
		/*write(STDERR_FILENO, ": command not found\n", 20);*/
		/*g_info->status = 127;*/
	/*}*/
	else
	{
		g_info->status = 1;
		write(STDERR_FILENO, cmd, ft_strlen(cmd));
		write(STDERR_FILENO, ": ", 2);
		perror(input);
	}
	if (err_code == ER_CMDNOTFND)
		g_info->status = 127;
}
