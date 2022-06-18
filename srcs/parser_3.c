/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladrian <ladrian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:41:13 by ladrian           #+#    #+#             */
/*   Updated: 2022/06/18 11:58:07 by ladrian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pre_find_envp(t_parser *parser, t_info *info)
{
	int	i;
	int	j;

	i = -1;
	while (parser->token[++i])
	{
		j = -1;
		while (parser->token[i][++j])
		{
			if (parser->token[i][j] == '$' && parser->token[i][j + 1])
			{
				find_envp(parser, i, info);
			}
		}
	}
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

char	*envp_with_symbols(char *str, char *value, char *key)
{
	int		i;
	int		j;
	int		k;
	char	*copy;

	i = find_dollar(str);
	copy = malloc(sizeof(char) *(ft_strlen(value)
				+ ft_strlen(str) - cmp_key(str, key) + 2));
	if (!copy)
		return (NULL);
	j = -1;
	while (++j < i)
		copy[j] = str[j];
	k = -1;
	while (value[++k])
		copy[i++] = value[k];
	while (str[j + cmp_key(str, key)])
	{
		copy[i++] = str[j + cmp_key(str, key) + 1];
		j++;
	}
	copy[i] = '\0';
	return (copy);
}
