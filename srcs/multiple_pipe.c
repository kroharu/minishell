#include "minishell.h"

static void	wait_all_proc(t_info *info, t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		waitpid(0, &info->status, 0);
		/*info->status = WEXITSTATUS(info->status);*/
		get_status(info);
		tmp = tmp->next;
	}
}

void	multiple_pipe(t_info *info, t_cmd *cmd)
{
	t_cmd	*tmp;
	t_cmd	*prev_tmp;
	pid_t	cpid;

	tmp = cmd;
	prev_tmp = 0;
	while (tmp)
	{
		if (tmp->next)
			pipe(tmp->pipefd);
		cpid = fork();
		if (cpid == -1)
		{
			close(tmp->pipefd[0]);
			close(tmp->pipefd[1]);
			error_exit(ER_FORK, 0);
		}
		else if (cpid == 0)
		{
			if (prev_tmp)
			{
				dup2(prev_tmp->pipefd[0], STDIN_FILENO);
				close(prev_tmp->pipefd[0]);
				close(prev_tmp->pipefd[1]);
			}
			if (tmp->next)
			{
				close(tmp->pipefd[0]);
				dup2(tmp->pipefd[1], STDOUT_FILENO);
				close(tmp->pipefd[1]);
			}
			exec_cmd(info, tmp);
			exit(info->status);
		}
			/*child_routine(info, &tmp, &prev_tmp);*/
		else
		{
			if (prev_tmp)
			{
				close(prev_tmp->pipefd[0]);
				close(prev_tmp->pipefd[1]);
			}
			prev_tmp = tmp;
			tmp = tmp->next;
		}
			/*parent_routine(&tmp, &prev_tmp);*/
	}
	wait_all_proc(info, cmd);
}
