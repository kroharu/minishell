/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 17:32:18 by cgoth             #+#    #+#             */
/*   Updated: 2022/07/04 17:32:28 by cgoth            ###   ########.fr       */
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

void	init_builtins(void *builtins[])
{
	builtins[0] = &echo;
	builtins[1] = &cd;
	builtins[2] = &env;
	builtins[3] = &export;
	builtins[4] = &ft_exit;
	builtins[5] = &pwd;
	builtins[6] = &unset;
}

void	init_blt_names(char *blt_names[])
{
	blt_names[0] = "echo";
	blt_names[1] = "cd";
	blt_names[2] = "env";
	blt_names[3] = "export";
	blt_names[4] = "exit";
	blt_names[5] = "pwd";
	blt_names[6] = "unset";
}

t_env	*init_env(char	**envp)
{
	t_env	*env_list;
	int		i;
	char	**split;

	i = -1;
	env_list = 0;
	while (envp[++i])
	{
		split = ft_split(envp[i], '=');
		env_list = ft_lstadd_back(env_list, \
				ft_lstnew(ft_strdup(split[0]), ft_strdup(split[1])));
		free_split(split);
		split = 0;
	}
	return (env_list);
}

t_cmd	*init_cmd(char **token, int pipe_cnt)
{
	t_cmd	*cmd;
	int		i;
	int		start;
	int		end;
	char	**tmp;

	cmd = 0;
	start = -1;
	end = 0;
	while (pipe_cnt-- != -1)
	{
		tmp = 0;
		while (token[end] && ft_strcmp(token[end], "|", -1) != 0)
			end++;
		tmp = malloc(sizeof(char *) *(end - start));
		if (!tmp)
			error_exit(ER_MALLOC);
		i = -1;
		while (++start < end)
			tmp[++i] = ft_strdup(token[start]);
		tmp[++i] = 0;
		cmd = ft_cmdadd_back(cmd, ft_cmdnew(tmp));
		end++;
	}
	return (cmd);
}
