#include "minishell.h"

void	execute(t_info *info)
{
	int pipe_cnt;
	
	if (info->token && ft_strcmp(info->token[0], "\0", -1) == 0)
		return ;
	pipe_cnt = check_pipes(info->token);
	info->cmd = init_cmd(info->token, pipe_cnt);
	check_redir(&info->cmd);
	if (info->cmd && info->cmd->token && *info->cmd->token != 0)
	{
		if (!pipe_cnt)
			exec_solocmd(info, info->cmd);
		else
			multiple_pipe(info, info->cmd);
	}
	free_cmd(info->cmd);
	info->cmd = 0;
}
