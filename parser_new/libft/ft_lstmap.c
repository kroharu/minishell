/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladrian <ladrian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 21:50:13 by ladrian           #+#    #+#             */
/*   Updated: 2021/10/14 16:52:38 by ladrian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*return_list;
	t_list	*work_el;

	work_el = ft_lstnew(f(lst->content));
	if (!work_el)
	{
		ft_lstclear(&lst, del);
		return (NULL);
	}
	return_list = work_el;
	lst = lst->next;
	while (lst)
	{
		work_el = ft_lstnew(f(lst->content));
		if (!work_el)
		{
			ft_lstclear(&lst, del);
			ft_lstclear(&work_el, del);
			break ;
		}
		lst = lst->next;
		ft_lstadd_back(&return_list, work_el);
	}
	return (return_list);
}
