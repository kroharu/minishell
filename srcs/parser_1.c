/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladrian <ladrian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:33:59 by ladrian           #+#    #+#             */
/*   Updated: 2022/06/18 13:25:01 by ladrian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_trim_qoutes(t_parser *parser, int i)
{
	int	j;
	int	k;

	parser->token[i] = malloc(sizeof(char)
			* (ft_strlen(parser->input[i]) + 1));
	k = 0;
	j = 0;
	while (parser->input[i][j])
	{		
		if (parser->input[i][j] == '\"' || parser->input[i][j] == '\'')
			j++;
		else
		{
			parser->token[i][k] = parser->input[i][j];
			j++;
			k++;
		}
	}
	parser->token[i][k] = '\0';
}

int	find_dollar(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] != '$')
			return (i);
	return (0);
}

static char	*loop(char *arr, t_env *lst)
{
	char	*tmp;
	char	*str;
	int		j;
	int		k;

	j = 0;
	str = arr;
	k = find_dollar(str) + 1;
	while (str[k] == lst->key[j] && str[k] && lst->key[j])
	{
		k++;
		j++;
	}
	if (lst->key[j] == '\0' && (str[k] == '\0' || str[k] == ' '))
	{
		tmp = str;
		if (find_dollar(str) == 0)
			str = ft_strdup(lst->value);
		else
			str = envp_with_symbols(str, lst->value, lst->key);
		free(tmp);
	}
	return (str);
}

void	find_envp(t_parser *parser, int envp, t_info *info)
{
	int		i;
	char	*tmp;
	char	**arr;
	t_env	*lst;

	lst = info->env_list;
	arr = parser->token;
	i = -1;
	while (arr[++i])
	{
		if (i == envp)
		{
			while (lst)
			{
				arr[i] = loop(arr[i], lst);
				lst = lst->next;
			}
		}
		else
		{
			tmp = arr[i];
			arr[i] = ft_strdup(arr[i]);
			free(tmp);
		}
	}
}

char	**parse_input(char *input, t_info *info)
{
	t_parser	parser;
	int			i;
	int			j;

	j = 0;
	parser.input = special_split(input, ' ', &i);
	if (parser.input)
		parser.input[i] = NULL;
	parser.token = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (parser.input[++i])
		ft_trim_qoutes(&parser, i);
	parser.token[i] = NULL;
	free_split(parser.input);
	parser.input = NULL;
	pre_find_envp(&parser, info);
	return (parser.token);
}
