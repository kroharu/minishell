#include "minishell.h"

t_env	*ft_lstlast(t_env *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
	}
	return (lst);
}

t_env	*ft_lstnew(char *key, char *value)
{
	t_env	*new_elem;

	new_elem = (t_env *)malloc(sizeof(t_env));
	if (!new_elem)
		error_exit(ER_MALLOC, 0);
	new_elem->key = key;
	new_elem->value = value;
	new_elem->next = NULL;
	return (new_elem);
}

t_env	*ft_lstadd_back(t_env *lst, t_env *new_lst)
{
	t_env	*tmp;

	if (!lst)
	{
		lst = new_lst;
		return (lst);
	}
	tmp = ft_lstlast(lst);
	new_lst->next = tmp->next;
	tmp->next = new_lst;
	return (lst);
}
