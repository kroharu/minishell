#include "minishell.h"

void	exec_cmd(t_info *info, t_cmd *cmd)
{
	int builtin;

	builtin = find_builtin(info);
	if (builtin >= 0)
	{
	    info->status = ((t_builtins)(info->builtins[builtin]))(info, cmd->token);
	    exit(info->status);
	}
	else
	{
	    if (execve(find_bin(info, cmd->token), cmd->token, info->envp))
	        error(ER_EXECVE);
	}
}

void	multiple_pipe(t_info *info, int pipe_cnt)
{
	t_cmd   *cmd;
	pid_t   cpid;
	int pipefd[2];
	
	cmd = init_cmd(info->token, pipe_cnt);
	while (pipe_cnt-- && cmd->next)
	{
	    pipe(pipefd);
	    cpid = fork();
	    if (cpid == 0)
	    {
	        close(pipefd[0]);
	        dup2(pipefd[1], STDOUT_FILENO);
	        exec_cmd(info, cmd);
	    }
	    else
	    {
	        waitpid(-1, &info->status, 0);
	        dup2(pipefd[0], STDIN_FILENO);
	        close(pipefd[1]);
	        cmd = cmd->next;
	    }
	}
	exec_cmd(info, cmd);
}

void	execute(t_info *info)
{
	int	blt_index;
	int pipe_cnt;
	
	pipe_cnt = check_pipes(info->token);
	if (!pipe_cnt)
	{
	    blt_index = find_builtin(info);
	    if (blt_index >= 0)
	        info->status = ((t_builtins)(info->builtins[blt_index]))(info, info->token);
	    else
	    {
	        if (execve(find_bin(info, info->token), info->token, info->envp))
	        	error(ER_EXECVE);
	    }
	}
	else
	    multiple_pipe(info, pipe_cnt);
}
