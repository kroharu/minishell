#include "minishell.h"

static void	wait_all_proc(t_info *info, t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		waitpid(0, &info->status, 0);
		get_status(info);
		tmp = tmp->next;
	}
}

static void	error_mp(int err_code, t_cmd *tmp, t_cmd *prev_tmp)
{
	if (prev_tmp)
	{
		close(prev_tmp->pipefd[0]);
		close(prev_tmp->pipefd[1]);
	}
	close(tmp->pipefd[0]);
	close(tmp->pipefd[1]);
	error_exit(err_code, 0);
}

static void	child_routine(t_info *info, t_cmd **curr, t_cmd **prev)
{
	t_cmd	*tmp;
	t_cmd	*prev_tmp;

	tmp = *curr;
	prev_tmp = *prev;
	if (prev_tmp)
	{
		if (dup2(prev_tmp->pipefd[0], STDIN_FILENO) == -1)
			error_mp(ER_DUP, tmp, prev_tmp);
		close(prev_tmp->pipefd[0]);
		close(prev_tmp->pipefd[1]);
	}
	if (tmp->next)
	{
		close(tmp->pipefd[0]);
		if (dup2(tmp->pipefd[1], STDOUT_FILENO) == -1)
			error_mp(ER_DUP, tmp, prev_tmp);
		close(tmp->pipefd[1]);
	}
	exec_cmd(info, tmp);
	exit(info->status);
}

static void	close_prev(t_cmd *prev_tmp)
{
	close(prev_tmp->pipefd[0]);
	close(prev_tmp->pipefd[1]);
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
			error_mp(ER_FORK, tmp, prev_tmp);
		else if (cpid == 0)
			child_routine(info, &tmp, &prev_tmp);
		else
		{
			if (prev_tmp)
				close_prev(prev_tmp);
			prev_tmp = tmp;
			tmp = tmp->next;
		}
	}
	wait_all_proc(info, cmd);
}
