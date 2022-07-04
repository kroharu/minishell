/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladrian <ladrian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 17:32:24 by ladrian           #+#    #+#             */
/*   Updated: 2022/07/04 20:49:55 by cgoth            ###   ########.fr       */
/*                                                                            */
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

int	find_reverse_pipe(char *token)
{
	int	i;

	i = -1;
	while (token[++i])
		;
	while (--i > -1)
	{
		if (ft_isalpha(token[i]) || ft_isdigit(token[i]))
			break ;
		else if (token[i] == '|')
			return (1);
	}
	return (0);
}

int	pipe_count(char *input, int *i)
{
	int	pipe_num;
	int	a;

	a = -1;
	pipe_num = 0;
	while (input[++a])
		if (input[a] == '|')
			pipe_num++;
	*i = a;
	return (pipe_num);
}

int	pipe_checker(char **input, int num)
{
	int	i;
	int	j;

	i = -1;
	if (find_pipe(input[0]) || find_reverse_pipe(input[num - 1]))
		return (1);
	while (++i < num - 1)
	{
		j = -1;
		if (find_reverse_pipe(input[i]) && find_pipe(input[i + 1]))
			return (1);
		while (input[i][++j + 1])
			if (input[i][j] == '|' && input[i][j + 1] == '|')
				return (1);
	}
	return (0);
}

int	find_pipe(char *token)
{
	int	i;

	i = -1;
	while (token && token[++i])
	{
		if (ft_isalpha(token[i]) || ft_isdigit(token[i]))
			break ;
		else if (token[i] == '|')
			return (1);
	}
	return (0);
}

char	*split_pipes(char *input)
{
	int		i;
	int		pipe_num;
	int		j;
	char	*pre_input;

	pipe_num = pipe_count(input, &i);
	pre_input = malloc(sizeof(char) * (i + pipe_num * 2 + 1));
	i = -1;
	j = -1;
	while (input[++i])
	{
		if (input[i] == '|')
		{
			pre_input[++j] = ' ';
			pre_input[++j] = '|';
			pre_input[++j] = ' ';
		}
		else
			pre_input[++j] = input[i];
	}
	pre_input[++j] = '\0';
	return (pre_input);
}
