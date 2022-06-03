#include "minishell.h"

static void	dup_hub(t_cmd *cmd)
{
	if (cmd->redir_fd_out != STDOUT_FILENO)
	{
		if (dup2(cmd->redir_fd_out, STDOUT_FILENO) < 0)
			error(ER_DUP);
		close(cmd->redir_fd_out);
	}
	if (cmd->redir_fd_in != STDIN_FILENO)
	{
		if (dup2(cmd->redir_fd_in, STDIN_FILENO) < 0)
			error(ER_DUP);
		close(cmd->redir_fd_in);
	}
}

static void	exec_cmd(t_info *info, t_cmd *cmd)
{
	int builtin;
	pid_t	cpid;

	builtin = find_builtin(info, cmd->token[0]);
	if (builtin >= 0)
	{
		dup_hub(cmd);
		info->status = ((t_builtins)(info->builtins[builtin]))(info, cmd->token);
		/*exit(info->status);*/
	}
	else
	{
		cpid = fork();
		if (cpid == 0)
		{
			dup_hub(cmd);
			if (execve(find_bin(info, cmd->token), cmd->token, info->envp))
				error(ER_EXECVE);
		}
		waitpid(cpid, &info->status, 0);
	}
}

static void	multiple_pipe(t_info *info, t_cmd *cmd)
{
	pid_t   cpid;
	int pipefd[2];
	int	flag;
	int old_out;

	cpid = 0;
	flag = 0;
	while (cmd->next && cpid == 0)
	{
		pipe(pipefd);
		cpid = fork();
		if (cpid == 0)
		{
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[1]);
			close(pipefd[0]);
			cmd = cmd->next;
			flag = 1;
		}
		else if (cpid > 0)
		{
			old_out = dup(STDOUT_FILENO);
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[0]);
			close(pipefd[1]);
			exec_cmd(info, cmd);
			dup2(old_out, STDOUT_FILENO);
			close(old_out);
			waitpid(cpid, &info->status, 0);
			if (flag)
				exit(info->status);
		}
		else if (cpid < 0)
			error(ER_FORK);
	}
	if (cpid == 0 && flag && !cmd->next)
	{
		exec_cmd(info, cmd);
		exit(info->status);
	}
}

void	execute(t_info *info)
{
	int pipe_cnt;
	t_cmd   *cmd;
	
	pipe_cnt = check_pipes(info->token);
	cmd = init_cmd(info->token, pipe_cnt);
	check_redir(&cmd);
	if (!pipe_cnt)
		exec_cmd(info, cmd);
	else
		multiple_pipe(info, cmd);
}
