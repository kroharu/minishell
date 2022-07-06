/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladrian <ladrian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:39:17 by ladrian           #+#    #+#             */
/*   Updated: 2022/07/06 13:49:59 by ladrian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*                      ⠸⡸⠜⠕⠕⠁⢁⢇⢏⢽⢺⣪⡳⡝⣎⣏⢯⢞⡿⣟⣷⣳⢯⡷⣽⢽⢯⣳⣫⠇                        */
/*                      ⠀⠀⢀⢀⢄⢬⢪⡪⡎⣆⡈⠚⠜⠕⠇⠗⠝⢕⢯⢫⣞⣯⣿⣻⡽⣏⢗⣗⠏⠀                        */
/*                      ⠀⠪⡪⡪⣪⢪⢺⢸⢢⢓⢆⢤⢀⠀⠀⠀⠀⠈⢊⢞⡾⣿⡯⣏⢮⠷⠁⠀⠀                         */
/*                      ⠀⠀⠀⠈⠊⠆⡃⠕⢕⢇⢇⢇⢇⢇⢏⢎⢎⢆⢄⠀⢑⣽⣿⢝⠲⠉⠀⠀⠀⠀                        */
/*                      ⠀⠀⠀⠀⠀⡿⠂⠠⠀⡇⢇⠕⢈⣀⠀⠁⠡⠣⡣⡫⣂⣿⠯⢪⠰⠂⠀⠀⠀⠀                        */
/*                      ⠀⠀⠀⠀⡦⡙⡂⢀⢤⢣⠣⡈⣾⡃⠠⠄⠀⡄⢱⣌⣶⢏⢊⠂⠀⠀⠀⠀⠀⠀                        */
/*                      ⠀⠀⠀⠀⢝⡲⣜⡮⡏⢎⢌⢂⠙⠢⠐⢀⢘⢵⣽⣿⡿⠁⠁⠀⠀⠀⠀⠀⠀⠀                        */
/*                      ⠀⠀⠀⠀⠨⣺⡺⡕⡕⡱⡑⡆⡕⡅⡕⡜⡼⢽⡻⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                        */
/*                      ⠀⠀⠀⠀⣼⣳⣫⣾⣵⣗⡵⡱⡡⢣⢑⢕⢜⢕⡝⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                        */
/*                      ⠀⠀⠀⣴⣿⣾⣿⣿⣿⡿⡽⡑⢌⠪⡢⡣⣣⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                        */
/*                      ⠀⠀⠀⡟⡾⣿⢿⢿⢵⣽⣾⣼⣘⢸⢸⣞⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                        */
/*                      ⠀⠀⠀⠀⠁⠇⠡⠩⡫⢿⣝⡻⡮⣒⢽⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                        */
/* ************************************************************************** */

#include "minishell.h"

t_list	*get_words(char *line, char separator)
{
	t_list	*words;
	char	*start;

	words = NULL;
	start = line;
	while (1)
	{
		line = special_strchr(line, separator, NULL);
		if (start != line)
			push_word(&words, start, line);
		if (!*line)
			break ;
		start = ++line;
	}
	return (words);
}

char	*special_strchr(char *line, char c, int *quote_flags)
{
	int	flags;

	if (quote_flags)
		flags = *quote_flags;
	else
		flags = 0;
	while (*line)
	{
		if (*line == '\'' && !(flags & 0x02))
			flags ^= 0x01;
		else if (*line == '\"' && !(flags & 0x01))
			flags ^= 0x02;
		else if (*line == c && !flags)
		{
			if (quote_flags)
				*quote_flags = flags;
			return (line);
		}
		line++;
	}
	if (quote_flags)
		*quote_flags = flags;
	return (line);
}

void	push_word(t_list **words, char *start, char *end)
{
	t_list	*new_word;
	int		word_len;
	char	*str;

	word_len = end - start + 1;
	str = safe_malloc((word_len + 1) * sizeof(char));
	new_word = ft_mylstnew(str);
	if (!new_word)
		fatal_error();
	ft_strlcpy(str, start, word_len);
	ft_mylstadd_back(words, new_word);
}

void	none(void *ptr)
{
	ptr = NULL;
	(void) ptr;
	return ;
}

void	**list_to_array(t_list *list, int *arr_size)
{
	t_list	*tmp;
	void	**arr;
	int		size;
	int		i;

	size = ft_lstsize(list);
	arr = safe_malloc((size + 1) * sizeof(void *));
	tmp = list;
	i = 0;
	while (tmp)
	{
		arr[i] = tmp->content;
		tmp = tmp->next;
		i++;
	}
	arr[size] = NULL;
	if (arr_size)
		*arr_size = size;
	return (arr);
}
