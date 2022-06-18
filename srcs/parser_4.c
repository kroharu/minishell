/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladrian <ladrian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:42:43 by ladrian           #+#    #+#             */
/*   Updated: 2022/06/16 16:45:05 by ladrian          ###   ########.fr       */
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

void	fatal_error(void)
{
	perror("fatal error: ");
	exit(EXIT_FAILURE);
}

void	*safe_malloc(size_t size)
{
	void	*p;

	p = malloc(size);
	if (!p)
		fatal_error();
	return (p);
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
