/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solocmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 17:33:26 by cgoth             #+#    #+#             */
/*   Updated: 2022/07/04 20:52:30 by cgoth            ###   ########.fr       */
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

static void	non_builtin_loop(t_info *info, t_cmd *cmd)
{
	pid_t	cpid;
	char	*path;

	cpid = fork();
	if (cpid == -1)
		error_exit(ER_FORK);
	else if (cpid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, sigquit_handler_child);
		path = find_bin(info, cmd->token);
		if (is_dir(path))
			error_dir(path);
		dup_hub(cmd);
		if (path && execve(path, cmd->token, info->envp))
			error(ER_EXECVE, "execve", 0, 0);
		exit(info->status);
	}
	if (cmd->redir_fd_in != STDIN_FILENO)
		close(cmd->redir_fd_in);
	waitpid(cpid, &info->status, 0);
	get_status(info);
	if (access("here_doc", F_OK) == 0 && unlink("here_doc"))
		error(ER_UNLINK, 0, 0, 0);
}

void	exec_solocmd(t_info *info, t_cmd *cmd)
{
	int	builtin;
	int	old_in;
	int	old_out;

	old_in = -1;
	old_out = -1;
	builtin = find_builtin(info, cmd->token[0]);
	update_envbin(info, cmd->token);
	update_envp(info);
	signal(SIGQUIT, sigquit_handler_parent);
	if (builtin >= 0)
	{
		if (cmd->redir_fd_in != STDIN_FILENO)
			old_in = dup(STDIN_FILENO);
		if (cmd->redir_fd_out != STDOUT_FILENO)
			old_out = dup(STDOUT_FILENO);
		dup_hub(cmd);
		info->status = ((t_builtins)(info->builtins[builtin]))(info, \
				cmd->token);
		if (old_in < 0 || old_out < 0)
			dup_back(old_in, old_out);
	}
	else
		non_builtin_loop(info, cmd);
}
