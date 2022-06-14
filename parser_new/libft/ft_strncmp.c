/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladrian <ladrian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:12:52 by ladrian           #+#    #+#             */
/*   Updated: 2021/10/13 20:49:08 by ladrian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	comparator(char c1, char c2)
{
	if ((unsigned char)c1 != (unsigned char)c2)
		return ((unsigned char)c1 - (unsigned char)c2);
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && (i < n))
	{
		if (comparator(s1[i], s2[i]))
			return (comparator(s1[i], s2[i]));
		i++;
	}
	if (i < n)
		return (comparator(s1[i], s2[i]));
	return (0);
}
