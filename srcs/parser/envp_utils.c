/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladrian <ladrian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 17:08:56 by ladrian           #+#    #+#             */
/*   Updated: 2022/07/03 18:55:27 by ladrian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_start_of_envp(int *j, int k, char *str)
{
	int	a;

	a = -1;
	*j = a;
	k = find_dollar(str);
	return (k);
}

int	find_dollar(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] != '$')
			return (i);
	return (-1);
}

int	cmp_key(char *str, char *key)
{
	int	begin;
	int	end;

	begin = find_dollar(str) + 1;
	end = -1;
	while (str[begin] == key[++end] && str[begin] && key [end])
		begin++;
	return (end);
}

t_list	*ft_mylstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}
