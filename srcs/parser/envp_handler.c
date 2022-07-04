/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladrian <ladrian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:41:13 by ladrian           #+#    #+#             */
/*   Updated: 2022/07/03 19:01:07 by ladrian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*envp_with_symbols(char *str, char *value, char *key)
{
	int		i;
	int		j;
	int		k;
	char	*copy;

	i = find_dollar(str);
	copy = malloc(sizeof(char) * (ft_strlen(value)
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

void	find_envp(t_parser *parser, int envp, t_info *info)
{
	int		i;
	char	*tmp;
	char	**arr;
	t_env	*lst;

	lst = info->env_list;
	arr = parser->input;
	i = -1;
	while (arr[++i])
	{
		if (i == envp)
			arr[i] = loop(arr[i], lst, info);
		else
		{
			tmp = arr[i];
			arr[i] = ft_strdup(arr[i]);
			free(tmp);
		}
	}
}

void	pre_find_envp(t_parser *parser, t_info *info)
{
	int	i;
	int	j;
	int	flag_1;
	int	flag_2;

	i = -1;
	flag_1 = 1;
	flag_2 = 1;
	while (parser->input[++i])
	{
		j = -1;
		while (parser->input[i][++j])
		{
			if (parser->input[i][j] == '\'')
				flag_1 *= -1;
			if (parser->input[i][j] == '\"' && flag_1 == 1)
				flag_2 *= -1;
			if (parser->input[i][j] == '$' && parser->input[i][j + 1]
					&& (flag_2 == -1 || flag_1 == 1))
				find_envp(parser, i, info);
		}
	}
}

char	*empty_envp(char *str, char *value, char *key)
{
	int		i;
	int		j;
	int		k;
	char	*copy;

	i = find_dollar(str);
	copy = malloc(sizeof(char) * (ft_strlen(value)
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
	free(key);
	copy[i] = '\0';
	return (copy);
}

char	*empty_envp_key(char *str)
{
	int		i;
	int		j;
	int		k;
	char	*copy;

	i = find_dollar(str);
	j = i;
	k = -1;
	while (str[++i])
		if (str[i] == ' ' || str[i] == '\'' || str[i] == '\"')
			break ;
	copy = malloc(sizeof(char) * (i - j + 1));
	if (!copy)
		return (NULL);
	while (j < i - 1)
		copy[++k] = str[++j];
	copy[++k] = '\0';
	return (copy);
}
