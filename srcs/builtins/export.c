/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 17:27:32 by cgoth             #+#    #+#             */
/*   Updated: 2022/07/04 17:41:19 by cgoth            ###   ########.fr       */
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

static int	check_add(char **arg)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = *arg;
	while (tmp[i + 1])
		i++;
	if (tmp[i] == '+')
	{
		tmp[i] = 0;
		return (1);
	}
	return (0);
}

static void	var_exists(t_info *info, char **split, int add_flag)
{
	t_env	*tmp;

	tmp = find_env(info->env_list, split[0]);
	if (add_flag)
		tmp->value = ft_strjoin(tmp->value, split[1], 1);
	else
	{
		if (tmp->value)
			free(tmp->value);
		if (split[1])
			tmp->value = ft_strdup(split[1]);
		else
			tmp->value = ft_strdup("");
	}
}

static void	new_var(t_info *info, char *arg)
{
	char	**split;
	int		add_flag;

	split = ft_split(arg, '=');
	add_flag = check_add(&(split[0]));
	if (find_env(info->env_list, split[0]))
		var_exists(info, split, add_flag);
	else
	{
		info->env_list = ft_lstadd_back(info->env_list, \
				ft_lstnew(ft_strdup(split[0]), ft_strdup(split[1])));
	}
	free_split(split);
}

static void	parse_args(t_info *info, char **args)
{
	int	i;

	i = 0;
	while (args[++i])
	{
		if (!valid_args(args[i]))
		{
			error(ER_EXPORT, "export", args[i], ": not a valid identifier\n");
			info->status = 1;
		}
		else
		{
			if (find_eq(args[i]))
				new_var(info, args[i]);
			else
			{
				if (find_env(info->env_list, args[i]) == 0)
					info->env_list = ft_lstadd_back(info->env_list, \
							ft_lstnew(ft_strdup(args[i]), 0));
			}
		}
	}
}

int	export(t_info *info, char **args)
{
	if (!args[1])
		empty_args(info->env_list);
	else
		parse_args(info, args);
	return (info->status);
}
