/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_7.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladrian <ladrian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 17:32:24 by ladrian           #+#    #+#             */
/*   Updated: 2022/07/03 15:23:49 by cgoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	write(fd, "\n", sizeof(char));
}

void	parse_error(int err_code)
{
	if (err_code < 0)
		error(err_code, 0, 0, "syntax error\n");
}

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
