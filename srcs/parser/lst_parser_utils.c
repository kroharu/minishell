/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_parser_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladrian <ladrian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:42:43 by ladrian           #+#    #+#             */
/*   Updated: 2022/07/03 18:57:13 by ladrian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_mylstadd_back(t_list **lst, t_list *new)
{
	if (*lst)
		ft_mylstlast(*lst)->next = new;
	else
		(*lst) = new;
}

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	del(lst->content);
	free(lst);
}

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*next;
	t_list	*current;

	if (!*lst)
		return ;
	current = *lst;
	next = current->next;
	ft_lstdelone(current, del);
	while (next)
	{
		current = next;
		next = current->next;
		ft_lstdelone(current, del);
	}
	*lst = NULL;
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
