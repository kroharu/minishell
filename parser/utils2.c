/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladrian <ladrian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 15:13:40 by ladrian           #+#    #+#             */
/*   Updated: 2022/04/30 18:22:27 by ladrian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniparser.h"

void	free_tokens(t_token **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		free_arr(tokens[i]->argv);
		free_arr(tokens[i]->in_files);
		free_arr(tokens[i]->in_red);
		free_arr(tokens[i]->out_files);
		free_arr(tokens[i]->out_red);
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

int	check_spaces(char *str)
{
	int	i;

	i = -1;
	while (*(str + ++i))
	{
		if (*(str + i) != ' ')
			return (1);
	}
	return (0);
}
