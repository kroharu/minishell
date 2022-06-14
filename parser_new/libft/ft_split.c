/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladrian <ladrian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 17:06:12 by ladrian           #+#    #+#             */
/*   Updated: 2021/10/13 23:03:32 by ladrian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	split_compare(const char c, char s)
{
	if (c == s)
		return (1);
	else
		return (0);
}

char	**ft_clear_splitted(char **split)
{
	unsigned int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}

static unsigned int	ft_get_nb_strs(char const *s, const char c)
{
	unsigned int	i;
	unsigned int	str_count;

	if (!s[0])
		return (0);
	i = 0;
	str_count = 0;
	while (s[i])
	{
		if (split_compare(c, s[i]))
			if (i > 0 && !split_compare(c, s[i - 1]))
				str_count++;
		i++;
	}
	if (!split_compare(c, s[i - 1]))
		str_count++;
	return (str_count);
}

static void	ft_get_next_str(char **next_str, unsigned int *next_str_len,
					const char c)
{
	unsigned int	i;

	*next_str += *next_str_len;
	*next_str_len = 0;
	i = 0;
	while (**next_str && split_compare(c, **next_str))
		(*next_str)++;
	while ((*next_str)[i])
	{
		if (split_compare(c, (*next_str)[i]))
			return ;
		(*next_str_len)++;
		i++;
	}
}

char	**ft_split(char const *s, const char c)
{
	char			**split;
	char			*next_str;
	unsigned int	next_str_len;
	unsigned int	str_nbr;
	unsigned int	i;

	str_nbr = ft_get_nb_strs(s, c);
	split = (char **)malloc(sizeof(char *) * (str_nbr + 1));
	if (!split)
		return (NULL);
	i = 0;
	next_str = (char *)s;
	next_str_len = 0;
	while (i < str_nbr)
	{
		ft_get_next_str(&next_str, &next_str_len, c);
		split[i] = malloc(sizeof(char) * (next_str_len + 1));
		if (!split[i])
			ft_clear_splitted(split);
		ft_strlcpy(split[i], next_str, next_str_len + 1);
		i++;
	}
	split[i] = NULL;
	return (split);
}
