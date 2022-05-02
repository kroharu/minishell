#include "minishell.h"

t_cmd	*ft_cmdlast(t_cmd *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
	}
	return (lst);
}

t_cmd	*ft_cmdnew(char **token)
{
	t_cmd	*new_elem;

	new_elem = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_elem)
		error(ER_MALLOC);
	new_elem->token = token;
	new_elem->next = NULL;
	return (new_elem);
}

t_cmd	*ft_cmdadd_back(t_cmd *lst, t_cmd *new_lst)
{
	t_cmd	*tmp;

	if (!lst)
	{
		lst = new_lst;
		return (lst);
	}
	tmp = ft_cmdlast(lst);
	new_lst->next = tmp->next;
	tmp->next = new_lst;
	return (lst);
}