/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladrian <ladrian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:44:22 by ladrian           #+#    #+#             */
/*   Updated: 2022/06/16 16:44:41 by ladrian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstsize(t_list *lst)
{
	int		size;

	if (!lst)
		return (0);
	size = 1;
	while (lst->next)
	{
		lst = lst->next;
		size++;
	}
	return (size);
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

t_list	*ft_mylstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (!(dst || src))
		return (0);
	if (dstsize == 0)
		return (ft_strlen(src));
	i = 0;
	while (*(src + i) && i < (dstsize - 1))
	{
		*(dst + i) = *(src + i);
		i++;
	}
	*(dst + i) = '\0';
	return (ft_strlen(src));
}
