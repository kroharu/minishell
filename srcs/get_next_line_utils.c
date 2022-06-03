/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 17:41:08 by cgoth             #+#    #+#             */
/*   Updated: 2022/05/19 18:17:32 by cgoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*free_gnl(char **s1, char **s2)
{
	free(*s1);
	free(*s2);
	return (NULL);
}

/*size_t	ft_strlen(const char *s)*/
/*{*/
	/*size_t	i;*/

	/*if (!s)*/
		/*return (0);*/
	/*i = 0;*/
	/*while (s[i])*/
		/*i++;*/
	/*return (i);*/
/*}*/

int	find_n(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	free_cache(char **s1)
{
	free(*s1);
	*s1 = NULL;
}

void	cache_gen(char **buf, char **cache, int r)
{
	(*buf)[r] = '\0';
	*cache = ft_strjoin(*cache, *buf, 1);
}
