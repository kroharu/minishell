/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_8.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladrian <ladrian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:44:07 by ladrian           #+#    #+#             */
/*   Updated: 2022/06/30 17:18:48 by ladrian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_dollar(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] != '$')
			return (i);
	return (-1);
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

int	ft_isdigit(int c)
{
	if ((c >= '0') && (c <= '9'))
		return (1);
	else
		return (0);
}

int	ft_isalpha(int c)
{
	if (((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z')))
		return (1);
	else
		return (0);
}
