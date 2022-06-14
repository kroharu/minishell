/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladrian <ladrian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:59:52 by ladrian           #+#    #+#             */
/*   Updated: 2021/10/13 23:46:40 by ladrian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	search;
	size_t	i;

	search = (unsigned char)c;
	i = 0;
	while (s[i])
		if (s[i++] == search)
			return ((char *)&s[--i]);
	if (s[i] == search)
		return ((char *)&s[i]);
	return (NULL);
}
