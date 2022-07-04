/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_empty_args.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 17:26:07 by cgoth             #+#    #+#             */
/*   Updated: 2022/07/04 17:34:13 by cgoth            ###   ########.fr       */
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

static char	**sort_copy(char **copy)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	while (copy[++i])
	{
		j = i;
		while (copy[++j])
		{
			if (ft_strcmp(copy[i], copy[j], -1) > 0)
			{
				tmp = copy[i];
				copy[i] = copy[j];
				copy[j] = tmp;
			}
		}
	}
	return (copy);
}

static void	print_copy(char **copy)
{
	int	i;

	i = -1;
	copy = sort_copy(copy);
	while (copy[++i])
		printf("declare -x %s\n", copy[i]);
	free_copy(copy);
}

static char	*fill_copy(char *copy, t_env *tmp)
{
	int	i;
	int	j;

	i = -1;
	while (tmp->key[++i])
		copy[i] = tmp->key[i];
	if (tmp->value)
	{
		copy[i] = '=';
		copy[++i] = '"';
		if (*tmp->value)
		{
			j = -1;
			while (tmp->value[++j])
				copy[++i] = tmp->value[j];
		}
		copy[++i] = '"';
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

static void	malloc_copies(t_env *env_list, char **copy, int len)
{
	t_env	*tmp;
	int		i;

	tmp = env_list;
	i = -1;
	while (++i < len && tmp)
	{
		if (!tmp->value)
			copy[i] = malloc(sizeof(char *) *(ft_strlen(tmp->key) + 1));
		else if (tmp->value && !*tmp->value)
			copy[i] = malloc(sizeof(char *) *(ft_strlen(tmp->key) + 4));
		else
		{
			copy[i] = malloc(sizeof(char *) *(ft_strlen(tmp->key) + \
						ft_strlen(tmp->value) + 4));
		}
		if (!copy)
			error_exit(ER_MALLOC);
		copy[i] = fill_copy(copy[i], tmp);
		tmp = tmp->next;
	}
}

void	empty_args(t_env *env_list)
{
	int		len;
	char	**copy;

	len = node_cnt(env_list);
	copy = malloc(sizeof(char *) *(len + 1));
	if (!copy)
		error_exit(ER_MALLOC);
	copy[len] = 0;
	malloc_copies(env_list, copy, len);
	print_copy(copy);
}
