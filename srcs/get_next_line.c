/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:25:24 by cgoth             #+#    #+#             */
/*   Updated: 2022/05/19 18:57:27 by cgoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static char	*ft_strdup(const char *s1)*/
/*{*/
	/*int		i;*/
	/*char	*copy;*/

	/*i = 0;*/
	/*copy = malloc(sizeof(char) *(ft_strlen(s1) + 1));*/
	/*if (!copy)*/
		/*return (NULL);*/
	/*while (s1[i])*/
	/*{*/
		/*copy[i] = s1[i];*/
		/*i++;*/
	/*}*/
	/*copy[i] = '\0';*/
	/*return (copy);*/
/*}*/

/*char	*ft_strjoin(char const *s1, char const *s2)*/
/*{*/
	/*int		i;*/
	/*int		j;*/
	/*char	*str;*/

	/*i = 0;*/
	/*j = 0;*/
	/*str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));*/
	/*if (!str)*/
		/*return (NULL);*/
	/*while (s1 && s1[i])*/
	/*{*/
		/*str[i] = s1[i];*/
		/*i++;*/
	/*}*/
	/*while (s2 && s2[j])*/
	/*{*/
		/*str[i + j] = s2[j];*/
		/*j++;*/
	/*}*/
	/*str[i + j] = '\0';*/
	/*free((void *)s1);*/
	/*return (str);*/
/*}*/

static char	*before_nl(const char *s1)
{
	size_t	i;
	char	*copy;

	copy = malloc(sizeof(char) *(ft_strlen(s1) + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (s1[i] && s1[i] != '\n')
	{
		copy[i] = s1[i];
		i++;
	}
	/*if (s1[i] == '\n')*/
	/*{*/
		/*copy[i] = '\n';*/
		/*i++;*/
	/*}*/
	copy[i] = '\0';
	if (i == 0 && copy[i] == 0)
	{
		free(copy);
		return (NULL);
	}
	return (copy);
}

static char	*after_nl(const char *s1)
{
	size_t	start;
	char	*tmp;

	start = 0;
	while (s1[start] && s1[start] != '\n')
		start++;
	if (!s1[start++])
		return (NULL);
	tmp = (char *)s1;
	s1 = ft_strdup(s1 + start);
	free((void *)tmp);
	return ((char *)s1);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buf;
	static char	*cache;
	int			r;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (NULL);
	r = 0;
	buf = malloc(sizeof(char) *(BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	while (!find_n(cache) && (r DEF read(fd, buf, BUFFER_SIZE)) > 0)
		cache_gen(&buf, &cache, r);
	if ((r == 0 || r == -1) && !cache)
		return (free_gnl(&cache, &buf));
	line = before_nl(cache);
	if (!line)
		return (free_gnl(&cache, &buf));
	if (find_n(cache))
		cache = after_nl(cache);
	else
		free_cache(&cache);
	free(buf);
	return (line);
}
