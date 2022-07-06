/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 17:30:40 by cgoth             #+#    #+#             */
/*   Updated: 2022/07/04 20:45:08 by cgoth            ###   ########.fr       */
/*—————————————————————————————————No norme?——————————————————————————————————*/
/*                      ⠀⣞⢽⢪⢣⢣⢣⢫⡺⡵⣝⡮⣗⢷⢽⢽⢽⣮⡷⡽⣜⣜⢮⢺⣜⢷⢽⢝⡽⣝                        */
/*                      ⠸⡸⠜⠕⠕⠁⢁⢇⢏⢽⢺⣪⡳⡝⣎⣏⢯⢞⡿⣟⣷⣳⢯⡷⣽⢽⢯⣳⣫⠇                        */
/*                      ⠀⠀⢀⢀⢄⢬⢪⡪⡎⣆⡈⠚⠜⠕⠇⠗⠝⢕⢯⢫⣞⣯⣿⣻⡽⣏⢗⣗⠏⠀                        */
/*                      ⠀⠪⡪⡪⣪⢪⢺⢸⢢⢓⢆⢤⢀⠀⠀⠀⠀⠈⢊⢞⡾⣿⡯⣏⢮⠷⠁⠀⠀                         */
/*                      ⠀⠀⠀⠈⠊⠆⡃⠕⢕⢇⢇⢇⢇⢇⢏⢎⢎⢆⢄⠀⢑⣽⣿⢝⠲⠉⠀⠀⠀⠀                        */
/*                      ⠀⠀⠀⠀⠀⡿⠂⠠⠀⡇⢇⠕⢈⣀⠀⠁⠡⠣⡣⡫⣂⣿⠯⢪⠰⠂⠀⠀⠀⠀                        */
/*                      ⠀⠀⠀⠀⡦⡙⡂⢀⢤⢣⠣⡈⣾⡃⠠⠄⠀⡄⢱⣌⣶⢏⢊⠂⠀⠀⠀⠀⠀⠀                        */
/*                      ⠀⠀⠀⠀⢝⡲⣜⡮⡏⢎⢌⢂⠙⠢⠐⢀⢘⢵⣽⣿⡿⠁⠁⠀⠀⠀⠀⠀⠀⠀                        */
/*                      ⠀⠀⠀⠀⠨⣺⡺⡕⡕⡱⡑⡆⡕⡅⡕⡜⡼⢽⡻⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                        */
/*                      ⠀⠀⠀⠀⣼⣳⣫⣾⣵⣗⡵⡱⡡⢣⢑⢕⢜⢕⡝⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                        */
/*                      ⠀⠀⠀⣴⣿⣾⣿⣿⣿⡿⡽⡑⢌⠪⡢⡣⣣⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                        */
/*                      ⠀⠀⠀⡟⡾⣿⢿⢿⢵⣽⣾⣼⣘⢸⢸⣞⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                        */
/*                      ⠀⠀⠀⠀⠁⠇⠡⠩⡫⢿⣝⡻⡮⣒⢽⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                        */
/* ************************************************************************** */

#include "minishell.h"

int	find_builtin(t_info *info, char *token)
{
	int	i;

	i = -1;
	while (++i < 7)
	{
		if (ft_strcmp(token, info->blt_names[i], -1) == 0)
			return (i);
	}
	return (-1);
}

static void	child_routine(t_info *info, t_cmd *cmd, int builtin)
{
	char	*path;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	dup_hub(cmd);
	if (builtin >= 0)
	{
		info->status = ((t_builtins)(info->builtins[builtin]))(info, \
				cmd->token);
		exit(info->status);
	}
	else
	{
		path = find_bin(info, cmd->token);
		if (is_dir(path))
			error_dir(path);
		if (path && execve(path, cmd->token, info->envp))
			error(ER_EXECVE, "execve", 0, 0);
		exit(info->status);
	}
}

void	get_status(t_info *info)
{
	if (WIFEXITED(info->status))
		info->status = WEXITSTATUS(info->status);
	else if (WIFSIGNALED(info->status))
		info->status = WTERMSIG(info->status) + 128;
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
		error_exit(ER_FORK);
	else if (cpid == 0)
	{
		child_routine(info, cmd, builtin);
	}
	signal(SIGQUIT, sigquit_handler_parent);
	if (cmd->redir_fd_in != STDIN_FILENO)
		close(cmd->redir_fd_in);
	waitpid(cpid, &info->status, 0);
	get_status(info);
	if (access("here_doc", F_OK) == 0 && unlink("here_doc"))
		error(ER_UNLINK, 0, 0, 0);
}
