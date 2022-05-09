/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladrian <ladrian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 13:20:17 by ladrian           #+#    #+#             */
/*   Updated: 2022/04/30 17:48:52 by ladrian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniparser.h"

int	parse_error(int code)
{
	if (code == QUOTE_ERR)
		ft_putendl_fd("error: unclosed qoutes", STDERR_FILENO);
	else if (code == PIPE_ERR)
		ft_putendl_fd("error: bad pipes", STDERR_FILENO);
	else if (code == FILE_ERR)
		ft_putendl_fd("error: missing file name", STDERR_FILENO);
	else if (code == FILE_ERR)
		ft_putendl_fd("error: incorrect redirection", STDERR_FILENO);
	else if (code == RED_ERR)
		ft_putendl_fd("mshl: syntax error near unexpected token",
			STDERR_FILENO);
	return (EXIT_FAILURE);
}

void	fatal_error(void)
{
	perror("fatal error: ");
	exit(EXIT_FAILURE);
}
