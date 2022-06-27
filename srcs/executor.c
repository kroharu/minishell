#include "minishell.h"

/*static void	mp_loop_parent()*/
/*{*/
	/*int	old_out;*/

	/*old_out = dup(STDOUT_FILENO);*/
	/*dup2(pipefd[1], STDOUT_FILENO);*/
	/*close(pipefd[0]);*/
	/*close(pipefd[1]);*/
	/*exec_cmd(info, cmd);*/
	/*dup2(old_out, STDOUT_FILENO);*/
	/*close(old_out);*/
	/*waitpid(info->cpid, &info->status, 0);*/
	/*if (*flag)*/
		/*exit(info->status);*/
/*}*/

/*static void	mp_loop_child()*/
/*{*/
	/*dup2(pipefd[0], STDIN_FILENO);*/
	/*close(pipefd[1]);*/
	/*close(pipefd[0]);*/
	/*cmd = cmd->next;*/
	/**flag = 1;*/
/*}*/

static void	exec_solocmd(t_info *info, t_cmd *cmd)
{
	int builtin;
	/*pid_t	cpid;*/
	int old_in;
	int old_out;

	old_in = -1;
	old_out = -1;
	info->last_flag = 1;
	builtin = find_builtin(info, cmd->token[0]);
	update_envbin(info, cmd->token);
	update_envp(info);
	signal(SIGQUIT, sigquit_handler_parent);
	if (builtin >= 0)
	{
		if (cmd->redir_fd_in != STDIN_FILENO)
			old_in = dup(STDIN_FILENO);
		if (cmd->redir_fd_out != STDOUT_FILENO)
			old_out= dup(STDOUT_FILENO);
		dup_hub(cmd);
		info->status = ((t_builtins)(info->builtins[builtin]))(info, cmd->token);
		if (old_in < 0 || old_out < 0)
			dup_back(old_in, old_out);
	}
	else
	{
		info->cpid = fork();
		if (info->cpid == -1)
			error_exit(ER_FORK);
		else if (info->cpid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, sigquit_handler_child);
			dup_hub(cmd);
			if (execve(find_bin(info, cmd->token), cmd->token, info->envp))
				error(ER_EXECVE);
		}
		if (cmd->redir_fd_in != STDIN_FILENO)
			close(cmd->redir_fd_in);
		waitpid(info->cpid, &info->status, 0);
		info->status = WEXITSTATUS(info->status);
        if (access("here_doc", F_OK) == 0 && unlink("here_doc"))
            error_exit(ER_UNLINK);
	}
}

void	execute(t_info *info)
{
	int pipe_cnt;
	
	if (info->token && ft_strcmp(info->token[0], "\0", -1) == 0)
		return ;
	pipe_cnt = check_pipes(info->token);
	info->cmd = init_cmd(info->token, pipe_cnt);
	check_redir(&info->cmd);
	if (!pipe_cnt)
		exec_solocmd(info, info->cmd);
	else
		multiple_pipe(info, info->cmd);
	free_cmd(info->cmd);
	info->cmd = 0;
}
