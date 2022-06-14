/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladrian <ladrian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:04:21 by ladrian           #+#    #+#             */
/*   Updated: 2021/10/13 23:47:31 by ladrian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	search;
	size_t	i;

	search = (unsigned char)c;
	i = 0;
	while (s[i])
		i++;
	while (i)
		if (s[i--] == search)
			return ((char *)&s[++i]);
	if (s[i] == search)
		return ((char *)&s[i]);
	return (NULL);
}
