/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 17:31:19 by cgoth             #+#    #+#             */
/*   Updated: 2022/07/04 17:31:29 by cgoth            ###   ########.fr       */
/*—————————————————————————————————No norme?——————————————————————————————————*/
/*						⠀⣞⢽⢪⢣⢣⢣⢫⡺⡵⣝⡮⣗⢷⢽⢽⢽⣮⡷⡽⣜⣜⢮⢺⣜⢷⢽⢝⡽⣝                        */
/*						⠸⡸⠜⠕⠕⠁⢁⢇⢏⢽⢺⣪⡳⡝⣎⣏⢯⢞⡿⣟⣷⣳⢯⡷⣽⢽⢯⣳⣫⠇                        */
/*						⠀⠀⢀⢀⢄⢬⢪⡪⡎⣆⡈⠚⠜⠕⠇⠗⠝⢕⢯⢫⣞⣯⣿⣻⡽⣏⢗⣗⠏⠀                        */
/*						⠀⠪⡪⡪⣪⢪⢺⢸⢢⢓⢆⢤⢀⠀⠀⠀⠀⠈⢊⢞⡾⣿⡯⣏⢮⠷⠁⠀⠀                         */
/*						⠀⠀⠀⠈⠊⠆⡃⠕⢕⢇⢇⢇⢇⢇⢏⢎⢎⢆⢄⠀⢑⣽⣿⢝⠲⠉⠀⠀⠀⠀                        */
/*						⠀⠀⠀⠀⠀⡿⠂⠠⠀⡇⢇⠕⢈⣀⠀⠁⠡⠣⡣⡫⣂⣿⠯⢪⠰⠂⠀⠀⠀⠀                        */
/*						⠀⠀⠀⠀⡦⡙⡂⢀⢤⢣⠣⡈⣾⡃⠠⠄⠀⡄⢱⣌⣶⢏⢊⠂⠀⠀⠀⠀⠀⠀                        */
/*						⠀⠀⠀⠀⢝⡲⣜⡮⡏⢎⢌⢂⠙⠢⠐⢀⢘⢵⣽⣿⡿⠁⠁⠀⠀⠀⠀⠀⠀⠀                        */
/*						⠀⠀⠀⠀⠨⣺⡺⡕⡕⡱⡑⡆⡕⡅⡕⡜⡼⢽⡻⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                        */
/*						⠀⠀⠀⠀⣼⣳⣫⣾⣵⣗⡵⡱⡡⢣⢑⢕⢜⢕⡝⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                        */
/*						⠀⠀⠀⣴⣿⣾⣿⣿⣿⡿⡽⡑⢌⠪⡢⡣⣣⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                        */
/*						⠀⠀⠀⡟⡾⣿⢿⢿⢵⣽⣾⣼⣘⢸⢸⣞⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                        */
/*						⠀⠀⠀⠀⠁⠇⠡⠩⡫⢿⣝⡻⡮⣒⢽⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                        */
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

static int	dir_searcher(char *split, char *cmd)
{
	DIR				*dirp;
	struct dirent	*dp;

	dirp = opendir(split);
	if (!dirp)
		return (FAIL);
	dp = readdir(dirp);
	while (dp)
	{
		if (ft_strcmp(dp->d_name, cmd, -1) == 0)
		{
			closedir(dirp);
			return (SUCCESS);
		}
		dp = readdir(dirp);
	}
	closedir(dirp);
	return (FAIL);
}

static int	check_path(t_info *info, char **cmd)
{
	if (access(cmd[0], F_OK) == 0 && access(cmd[0], X_OK) == 0)
		return (1);
	error(ER_ACCESS, cmd[0], 0, "Permission denied\n");
	info->status = 126;
	return (0);
}

static char	*gen_path(char **split, char *cmd, int i)
{
	char	*path;

	path = ft_strjoin(split[i], "/", 0);
	path = ft_strjoin(path, cmd, 1);
	free_split(split);
	return (path);
}

char	*find_bin(t_info *info, char **cmd)
{
	t_env	*tmp;
	char	*path;
	char	**split;
	int		i;

	if (cmd[0][0] == '/' || cmd[0][0] == '.')
	{
		if (check_path(info, cmd))
			return (cmd[0]);
		return (0);
	}
	tmp = find_env(info->env_list, "PATH");
	split = ft_split(tmp->value, ':');
	i = -1;
	while (split[++i])
	{
		if (dir_searcher(split[i], cmd[0]))
		{
			path = gen_path(split, cmd[0], i);
			return (path);
		}
	}
	free_split(split);
	error(ER_CMDNOTFND, cmd[0], 0, ": command not found\n");
	return (0);
}
