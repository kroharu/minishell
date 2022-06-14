/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladrian <ladrian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 14:27:37 by ladrian           #+#    #+#             */
/*   Updated: 2022/04/30 17:48:03 by ladrian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniparser.h"

void	push_word(t_list **words, char *start, char *end)
{
	t_list	*new_word;
	int		word_len;
	char	*str;

	word_len = end - start + 1;
	str = safe_malloc((word_len + 1) * sizeof(char));
	new_word = ft_lstnew(str);
	if (!new_word)
		fatal_error();
	ft_strlcpy(str, start, word_len);
	ft_lstadd_back(words, new_word);
}

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

char	**special_split(char *line, char separator, int *size)
{
	t_list	*words;
	char	**arr;

	words = get_words(line, separator);
	arr = (char **)list_to_array(words, size);
	ft_lstclear(&words, &none);
	return (arr);
}
