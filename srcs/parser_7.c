/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_7.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladrian <ladrian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 17:32:24 by ladrian           #+#    #+#             */
/*   Updated: 2022/06/18 17:33:01 by ladrian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	write(fd, "\n", sizeof(char));
}

void	parse_error(int error)
{
	if (error == QUOTE_ERR)
		ft_putendl_fd("error: unclosed qoutes", STDERR_FILENO);
	else if (error == PIPE_ERR)
		ft_putendl_fd("error: bad pipes", STDERR_FILENO);
}
