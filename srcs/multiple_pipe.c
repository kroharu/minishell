#include "minishell.h"

static void	child_routine(t_info *info, t_cmd *cmd, int builtin)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	dup_hub(cmd);
	if (builtin >= 0)
	{
		info->status = ((t_builtins)(info->builtins[builtin]))(info, cmd->token);
		exit(info->status);
	}
	else
	{
		if (execve(find_bin(info, cmd->token), cmd->token, info->envp))
			error(ER_EXECVE);
		exit(ER_EXECVE);
	}
}

static void	exec_cmd(t_info *info, t_cmd *cmd)
{
	int		builtin;
	pid_t	cpid;

	builtin = find_builtin(info, cmd->token[0]);
	update_envbin(info, cmd->token, builtin);
	update_envp(info);
	cpid = fork();
	if (cpid == 0)
	{
		child_routine(info, cmd, builtin);
	}
	signal(SIGQUIT, sigquit_handler_parent);
	if (cmd->redir_fd_in != STDIN_FILENO)
		close(cmd->redir_fd_in);
	waitpid(cpid, &info->status, 0);
	if (access("here_doc", F_OK) == 0 && unlink("here_doc"))
		error(ER_UNLINK);
}

/*void	multiple_pipe(t_info *info, t_cmd *cmd)*/
/*{*/
	/*[>pid_t   cpid;<]*/
	/*int pipefd[2];*/
	/*int	flag;*/
	/*int old_out;*/

	/*info->cpid = 0;*/
	/*flag = 0;*/
	/*while (cmd->next && info->cpid == 0)*/
	/*{*/
		/*pipe(pipefd);*/
		/*info->cpid = fork();*/
		/*if (info->cpid < 0)*/
			/*error(ER_FORK);*/
		/*if (info->cpid == 0)*/
		/*{*/
			/*dup2(pipefd[0], STDIN_FILENO);*/
			/*close(pipefd[1]);*/
			/*close(pipefd[0]);*/
			/*cmd = cmd->next;*/
			/*flag = 1;*/
		/*}*/
			/*[>mp_loop_child(cmd, &pipefd, &flag);<]*/
		/*else if (info->cpid > 0)*/
		/*{*/
			/*old_out = dup(STDOUT_FILENO);*/
			/*dup2(pipefd[1], STDOUT_FILENO);*/
			/*close(pipefd[0]);*/
			/*close(pipefd[1]);*/
			/*exec_cmd(info, cmd);*/
			/*dup2(old_out, STDOUT_FILENO);*/
			/*close(old_out);*/
			/*waitpid(info->cpid, &info->status, 0);*/
			/*if (flag)*/
				/*exit(info->status);*/
		/*}*/
			/*[>mp_loop_parent(info, cmd, &pipefd);<]*/
		/*[>mp_loop_body(info, cmd, &flag);<]*/
	/*}*/
	/*if (info->cpid == 0 && flag && !cmd->next)*/
	/*{*/
		/*info->last_flag = 1;*/
		/*exec_cmd(info, cmd);*/
		/*exit(info->status);*/
	/*}*/
/*}*/

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
			perror(": fork");
			exit(info->status);
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
	}
	tmp = cmd;
	while (tmp)
	{
		waitpid(0, &info->status, 0);
		tmp = tmp->next;
	}
}
