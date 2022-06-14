/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladrian <ladrian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 10:25:57 by ladrian           #+#    #+#             */
/*   Updated: 2022/06/13 10:25:58 by ladrian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniparser.h"

void	copy_envp(char **envp)
{
	char	*tmp;

	while (*envp)
	{
		tmp = ft_strdup(*envp);
		if (!tmp)
			fatal_error();
		safe_lstadd_back(&g_data.envp, tmp);
		envp++;
	}
}

t_list	*find_var(char *name)
{
	t_list	*tmp;

	tmp = g_data.envp;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, name, ft_strlen(name))
			&& *(char *)(tmp->content + ft_strlen(name)) == '=')
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*ft_getenv(char *name)
{
	t_list	*var;

	var = find_var(name);
	if (var)
		return (var->content + ft_strlen(name) + 1);
	else
		return (NULL);
}

void	ft_setenv(char *name, char *value)
{
	t_list	*var;
	char	*new;

	new = NULL;
	append_str(&new, name);
	append_str(&new, "=");
	append_str(&new, value);
	var = find_var(name);
	if (var)
	{
		ft_putendl_fd("HUI", STDOUT_FILENO);
		free(var->content);
		var->content = new;
	}
	else
		safe_lstadd_back(&g_data.envp, new);
}

void	ft_unsetenv(char *name)
{
	t_list	*var;

	var = find_var(name);
	if (var)
		lst_remove(&g_data.envp, var);
}
