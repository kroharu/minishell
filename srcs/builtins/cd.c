/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 17:19:38 by cgoth             #+#    #+#             */
/*   Updated: 2022/07/04 17:40:35 by cgoth            ###   ########.fr       */
/*—————————————————————————————————No norme?——————————————————————————————————*/
/*                      ⠀⣞⢽⢪⢣⢣⢣⢫⡺⡵⣝⡮⣗⢷⢽⢽⢽⣮⡷⡽⣜⣜⢮⢺⣜⢷⢽⢝⡽⣝                    */
/*                      ⠸⡸⠜⠕⠕⠁⢁⢇⢏⢽⢺⣪⡳⡝⣎⣏⢯⢞⡿⣟⣷⣳⢯⡷⣽⢽⢯⣳⣫⠇                    */
/*                      ⠀⠀⢀⢀⢄⢬⢪⡪⡎⣆⡈⠚⠜⠕⠇⠗⠝⢕⢯⢫⣞⣯⣿⣻⡽⣏⢗⣗⠏⠀                    */
/*                      ⠀⠪⡪⡪⣪⢪⢺⢸⢢⢓⢆⢤⢀⠀⠀⠀⠀⠈⢊⢞⡾⣿⡯⣏⢮⠷⠁⠀⠀                     */
/*                      ⠀⠀⠀⠈⠊⠆⡃⠕⢕⢇⢇⢇⢇⢇⢏⢎⢎⢆⢄⠀⢑⣽⣿⢝⠲⠉⠀⠀⠀⠀                    */
/*                      ⠀⠀⠀⠀⠀⡿⠂⠠⠀⡇⢇⠕⢈⣀⠀⠁⠡⠣⡣⡫⣂⣿⠯⢪⠰⠂⠀⠀⠀⠀                    */
/*                      ⠀⠀⠀⠀⡦⡙⡂⢀⢤⢣⠣⡈⣾⡃⠠⠄⠀⡄⢱⣌⣶⢏⢊⠂⠀⠀⠀⠀⠀⠀                    */
/*                      ⠀⠀⠀⠀⢝⡲⣜⡮⡏⢎⢌⢂⠙⠢⠐⢀⢘⢵⣽⣿⡿⠁⠁⠀⠀⠀⠀⠀⠀⠀                    */
/*                      ⠀⠀⠀⠀⠨⣺⡺⡕⡕⡱⡑⡆⡕⡅⡕⡜⡼⢽⡻⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                    */
/*                      ⠀⠀⠀⠀⣼⣳⣫⣾⣵⣗⡵⡱⡡⢣⢑⢕⢜⢕⡝⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                    */
/*                      ⠀⠀⠀⣴⣿⣾⣿⣿⣿⡿⡽⡑⢌⠪⡢⡣⣣⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                    */
/*                      ⠀⠀⠀⡟⡾⣿⢿⢿⢵⣽⣾⣼⣘⢸⢸⣞⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                    */
/*                      ⠀⠀⠀⠀⠁⠇⠡⠩⡫⢿⣝⡻⡮⣒⢽⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                    */
/* ************************************************************************** */

#include "minishell.h"

static void	update_oldpwd(t_info *info)
{
	t_env	*tmp;
	char	*oldpwd;

	oldpwd = 0;
	tmp = find_env(info->env_list, "PWD");
	if (tmp)
		oldpwd = ft_strdup(tmp->value);
	tmp = find_env(info->env_list, "OLDPWD");
	if (!tmp)
		info->env_list = ft_lstadd_back(info->env_list, \
				ft_lstnew("OLDPWD", oldpwd));
	else
	{
		free(tmp->value);
		tmp->value = oldpwd;
	}
}

static void	update_pwd(t_info *info)
{
	t_env	*tmp;
	char	*path;

	tmp = find_env(info->env_list, "PWD");
	path = getcwd(0, 0);
	if (!path)
		return (error(ER_GETCWD, "getcwd", 0, 0));
	if (tmp)
	{
		if (tmp->value)
			free(tmp->value);
		tmp->value = path;
	}
}

static char	*move_to_root(t_info *info)
{
	char	*root;
	t_env	*tmp;

	tmp = find_env(info->env_list, "HOME");
	if (!tmp)
		root = "/Users/cgoth";
	else
		root = tmp->value;
	return (root);
}

static void	minus(t_info *info)
{
	char	*old_path;
	t_env	*pwd_node;
	t_env	*oldpwd_node;

	oldpwd_node = find_env(info->env_list, "OLDPWD");
	if (!oldpwd_node || !oldpwd_node->value || !*oldpwd_node->value)
		return (error(ER_CDMINUS, "cd", 0, "OLDPWD not set\n"));
	old_path = ft_strdup(oldpwd_node->value);
	free(oldpwd_node->value);
	if (chdir(old_path) == -1)
		return (error(ER_CHDIR, "cd", old_path, 0));
	printf("%s\n", old_path);
	pwd_node = find_env(info->env_list, "PWD");
	if (pwd_node && pwd_node->value)
	{
		oldpwd_node->value = ft_strdup(pwd_node->value);
		free(pwd_node->value);
		pwd_node->value = ft_strdup(old_path);
	}
	else
		oldpwd_node->value = ft_strdup("");
	free(old_path);
}

int	cd(t_info *info, char **args)
{
	char	*path;

	if (!args[1] || ft_strcmp(args[1], "~", -1) == 0 || \
			ft_strcmp(args[1], "~/", -1) == 0)
		path = move_to_root(info);
	else
		path = args[1];
	if (ft_strcmp(path, "-", -1) == 0)
		minus(info);
	else if (chdir(path) != -1)
	{
		update_oldpwd(info);
		update_pwd(info);
	}
	else
		error(ER_CHDIR, "cd", path, 0);
	return (info->status);
}
