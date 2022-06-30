/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladrian <ladrian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 17:29:21 by ladrian           #+#    #+#             */
/*   Updated: 2022/06/30 17:33:12 by ladrian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_handler(char **input, int num)
{
	if (pipe_checker(input, num))
		return (PIPE_ERR);
	if (quote_checker(input))
		return (QUOTE_ERR);
	if (redir_checker(input))
		return (REDIR_ERR);
	return (0);
}

int	redir_checker(char **input)
{
	if (!input[1] && (input[0][0] == '<' || input[0][0] == '>'))
		return (1);
	return (0);
}

int	quote_checker(char **input)
{
	int	flag_1;
	int	flag_2;
	int	i;
	int	j;

	i = -1;
	flag_1 = 1;
	flag_2 = 1;
	while (input[++i])
	{
		j = -1;
		while (input[i][++j])
		{
			if (input[i][j] == '\"')
				flag_2 *= -1;
			if (input[i][j] == '\'')
				flag_1 *= -1;
		}
		if (flag_1 != 1 || flag_2 != 1)
			return (1);
	}
	return (0);
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
	while (token[++i])
	{
		if (ft_isalpha(token[i]) || ft_isdigit(token[i]))
			break ;
		else if (token[i] == '|')
			return (1);
	}
	return (0);
}
