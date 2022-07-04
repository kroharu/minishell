/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 17:30:16 by cgoth             #+#    #+#             */
/*   Updated: 2022/07/04 17:42:21 by cgoth            ###   ########.fr       */
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

static int	envlist_len(t_env *env_list)
{
	t_env	*tmp;
	int		cnt;

	cnt = 0;
	tmp = env_list;
	while (tmp)
	{
		if (tmp->value)
			cnt++;
		tmp = tmp->next;
	}
	return (cnt);
}

void	update_shlvl(t_info *info)
{
	t_env	*tmp;
	char	*ptr;

	tmp = find_env(info->env_list, "SHLVL");
	if (tmp)
	{
		ptr = tmp->value;
		tmp->value = ft_itoa(ft_atoi(tmp->value) + 1);
		free(ptr);
	}
}

void	update_envbin(t_info *info, char **token)
{
	t_env	*tmp;
	char	*path;

	path = 0;
	tmp = info->env_list;
	tmp = find_env(tmp, "_");
	if (tmp && token)
	{
		if (tmp->value)
			free(tmp->value);
		tmp->value = ft_strdup(token[0]);
	}
}

static void	loop(t_info *info, t_env *tmp, int i)
{
	char	*value;

	value = ft_strjoin("=", tmp->value, 0);
	info->envp[i] = ft_strjoin(tmp->key, value, 0);
	free(value);
	if (!info->envp[i])
	{
		free_split(info->envp);
		error_exit(ER_MALLOC);
	}
}

void	update_envp(t_info *info)
{
	int		cnt;
	int		i;
	t_env	*tmp;

	tmp = info->env_list;
	cnt = envlist_len(info->env_list);
	free_split(info->envp);
	info->envp = malloc(sizeof(char *) * (cnt + 1));
	if (!info->envp)
		error_exit(ER_MALLOC);
	info->envp[cnt] = 0;
	i = 0;
	while (tmp && i < cnt)
	{
		if (tmp->key && tmp->value)
		{
			loop(info, tmp, i);
			i++;
		}
		tmp = tmp->next;
	}
}
