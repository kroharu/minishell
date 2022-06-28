#include "minishell.h"

static void	child_routine(t_info *info, t_cmd *cmd, int builtin)
{
	char	*path;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	dup_hub(cmd);
	if (builtin >= 0)
	{
		info->status = ((t_builtins)(info->builtins[builtin]))(info,\
				cmd->token);
		exit(info->status);
	}
	else
	{
		path = find_bin(info, cmd->token);
		if (is_dir(path))
			error_exit(ER_CMDDIR, 0);
		if (path && execve(path, cmd->token, info->envp))
			error_exit(ER_EXECVE, 0);
		/*exit(ER_EXECVE);*/
	}
}

void	exec_cmd(t_info *info, t_cmd *cmd)
{
	int		builtin;
	pid_t	cpid;

	builtin = find_builtin(info, cmd->token[0]);
	update_envbin(info, cmd->token);
	update_envp(info);
	cpid = fork();
	if (cpid == -1)
		error_exit(ER_FORK, 0);
	else if (cpid == 0)
	{
		child_routine(info, cmd, builtin);
	}
	signal(SIGQUIT, sigquit_handler_parent);
	if (cmd->redir_fd_in != STDIN_FILENO)
		close(cmd->redir_fd_in);
	waitpid(cpid, &info->status, 0);
	info->status = WEXITSTATUS(info->status);
	if (access("here_doc", F_OK) == 0 && unlink("here_doc"))
		error_exit(ER_UNLINK, 0);
}
