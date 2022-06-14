/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladrian <ladrian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 15:16:39 by ladrian           #+#    #+#             */
/*   Updated: 2022/04/30 17:47:13 by ladrian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniparser.h"

int	check_redirections(t_list *red)
{
	t_list	*tmp;

	tmp = red;
	while (tmp)
	{
		if (ft_strcmp(">", tmp->content)
			&& ft_strcmp("<", tmp->content)
			&& ft_strcmp(">>", tmp->content)
			&& ft_strcmp("<<", tmp->content))
		{
			parse_error(RED_ERR);
			return (EXIT_FAILURE);
		}
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

void	trim_word(char **word)
{
	char	*buf;
	char	*tmp;
	char	c;
	int		i;

	tmp = *word;
	i = 0;
	c = 0;
	buf = safe_malloc((ft_strlen(tmp) + 1) * sizeof(char));
	while (*tmp)
	{
		if ((*tmp == '\'' || *tmp == '\"')
			&& (c == 0 || c == *tmp))
			c ^= *tmp;
		else
			buf[i++] = *tmp;
		tmp++;
	}
	buf[i] = '\0';
	tmp = ft_strdup(buf);
	free(buf);
	if (!tmp)
		fatal_error();
	free(*word);
	*word = tmp;
}

void	words_processing(t_list **list)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp)
	{
		parse_vars((char **)&tmp->content);
		tmp = tmp->next;
	}
	tmp = *list;
	while (tmp)
	{
		if (!*(char *)(tmp->content))
		{
			lst_remove(list, tmp);
			tmp = *list;
		}
		else
			tmp = tmp->next;
	}
	tmp = *list;
	while (tmp)
	{
		trim_word((char **)&tmp->content);
		tmp = tmp->next;
	}
}

t_list	*split_word(char *word)
{
	t_list	*words;
	char	*start;

	words = NULL;
	while (1)
	{
		start = word;
		if (special_strchr(word, '>', NULL)
			> special_strchr(word, '<', NULL))
			word = special_strchr(word, '<', NULL);
		else
			word = special_strchr(word, '>', NULL);
		if (start != word)
			push_word(&words, start, word);
		if (!*word)
			break ;
		start = word;
		while (*word == '>' || *word == '<')
			word++;
		push_word(&words, start, word);
	}
	return (words);
}
