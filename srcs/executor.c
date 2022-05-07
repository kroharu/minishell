#include "minishell.h"

void	exec_cmd(t_info *info, char **token)
{
	int builtin;
	pid_t	cpid;

	builtin = find_builtin(info, token[0]);
	if (builtin >= 0)
	{
	    info->status = ((t_builtins)(info->builtins[builtin]))(info, token);
	}
	else
	{
		cpid = fork();
		if (cpid == 0)
		{
			if (execve(find_bin(info, token), token, info->envp))
				error(ER_EXECVE);
		}
		/*waitpid(-1, &info->status, 0);*/
	}
}

void	multiple_pipe(t_info *info, int pipe_cnt)
{
	t_cmd   *cmd;
	pid_t   cpid;
	int pipefd[2];

	cmd = init_cmd(info->token, pipe_cnt);
	cpid = fork();
	if (cpid < 0)
		error(ER_FORK);
	else if (cpid == 0)
	{
		while (cmd->next && cpid == 0)
		{
			pipe(pipefd);
			cpid = fork();
			if (cpid == 0)
			{
				close(pipefd[1]);
				dup2(pipefd[0], STDIN_FILENO);
				cmd = cmd->next;
			}
			else if (cpid > 0)
			{
				close(pipefd[0]);
				dup2(pipefd[1], STDOUT_FILENO);
				exec_cmd(info, cmd->token);
				waitpid(-1, &info->status, 0);
				exit(info->status);
			}
			else
				error(ER_FORK);
		}
		if (cpid == 0 && !cmd->next)
		{
			/*close(pipefd[0]);*/
			/*dup2(pipefd[1], STDIN_FILENO);*/
			exec_cmd(info, cmd->token);
			waitpid(-1, &info->status, 0);
			exit(info->status);
		}
		waitpid(-1, &info->status, 0);
	}
	waitpid(-1, &info->status, 0);
}

void	execute(t_info *info)
{
	int	blt_index;
	int pipe_cnt;
	pid_t	cpid;
	
	pipe_cnt = check_pipes(info->token);
	if (!pipe_cnt)
	{
	    blt_index = find_builtin(info, info->token[0]);
	    if (blt_index >= 0)
	        info->status = ((t_builtins)(info->builtins[blt_index]))(info, info->token);
	    else
	    {
			cpid = fork();
			if (cpid == 0)
			{
	        	if (execve(find_bin(info, info->token), info->token, info->envp))
	        		error(ER_EXECVE);
			}
			waitpid(-1, &info->status, 0);
	    }
	}
	else
	    multiple_pipe(info, pipe_cnt);
}
