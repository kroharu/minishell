/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladrian <ladrian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:51:13 by ladrian           #+#    #+#             */
/*   Updated: 2021/10/16 15:38:43 by ladrian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	size_t	begin;
	size_t	end;
	size_t	i;

	begin = 0;
	while (s1[begin] && check_set(s1[begin], set))
		begin++;
	end = ft_strlen(s1);
	while (end > begin && check_set(s1[end - 1], set))
		end--;
	res = (char *)malloc(sizeof(*s1) * (end - begin + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (begin < end)
		res[i++] = s1[begin++];
	res[i] = 0;
	return (res);
}
