/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladrian <ladrian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 15:05:31 by ladrian           #+#    #+#             */
/*   Updated: 2022/04/30 17:46:25 by ladrian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniparser.h"

int	name_length(char *p)
{
	int	len;

	len = 0;
	if (ft_isdigit(*p))
		return (1);
	while (ft_isalnum(*(p + len)) || *(p + len) == '_')
		len++;
	return (len);
}

char	*get_value(char *p, int len)
{
	char	*name;
	char	*value;

	if (ft_isdigit(*p))
		return (ft_strdup(""));
	name = safe_malloc((len + 1) * sizeof(char));
	ft_strlcpy(name, p, len + 1);
	value = ft_getenv(name);
	if (value)
		value = ft_strdup(value);
	else
		value = ft_strdup("");
	free(name);
	return (value);
}

void	add_var(t_list **parts, char **start, char **p)
{
	char	*value;
	int		len;

	if (*start != *p)
		push_word(parts, *start, *p);
	(*p)++;
	len = name_length(*p);
	if (len)
	{
		value = get_value(*p, len);
		*p += len;
	}
	else
	{
		value = ft_itoa(g_data.exit_code);
		(*p)++;
	}
	if (!value)
		fatal_error();
	safe_lstadd_back(parts, value);
	*start = *p;
}

t_list	*get_word_parts(char *word)
{
	t_list	*parts;
	char	*start;
	char	*tmp;
	int		flags;

	parts = NULL;
	tmp = word;
	start = tmp;
	flags = 0;
	while (*tmp)
	{
		if (*tmp == '\'' && !(flags & 0x02))
			flags ^= 0x01;
		else if (*tmp == '\"' && !(flags & 0x01))
			flags ^= 0x02;
		if (*tmp == '$' && !(flags & 0x01)
			&& (ft_isalnum(*(tmp + 1)) || ft_strchr("?_", *(tmp + 1))))
			add_var(&parts, &start, &tmp);
		else
			tmp++;
	}
	if (start != tmp)
		push_word(&parts, start, tmp);
	return (parts);
}

void	parse_vars(char **word)
{
	t_list	*parts;
	t_list	*tmp;
	char	*new;

	parts = get_word_parts(*word);
	free(*word);
	tmp = parts;
	new = NULL;
	while (tmp)
	{
		append_str(&new, tmp->content);
		tmp = tmp->next;
	}
	ft_lstclear(&parts, &free);
	*word = new;
}
