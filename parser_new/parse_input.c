/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladrian <ladrian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 14:14:22 by ladrian           #+#    #+#             */
/*   Updated: 2022/04/30 18:02:45 by ladrian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniparser.h"

void	sort_and_fill(t_token *token, t_list *files, t_list *red, int *i)
{
	t_list	*list_arr[4];

	ft_memset(list_arr, 0, 4 * sizeof(t_list *));
	while (files && red)
	{
		if (!ft_strcmp(red->content, "<") || !ft_strcmp(red->content, "<<"))
		{
			safe_lstadd_back(&list_arr[0], files->content);
			safe_lstadd_back(&list_arr[1], red->content);
		}
		else
		{
			safe_lstadd_back(&list_arr[2], files->content);
			safe_lstadd_back(&list_arr[3], red->content);
		}
		files = files->next;
		red = red->next;
	}
	token->in_files = (char **)list_to_array(list_arr[0], NULL);
	token->in_red = (char **)list_to_array(list_arr[1], NULL);
	token->out_files = (char **)list_to_array(list_arr[2], NULL);
	token->out_red = (char **)list_to_array(list_arr[3], NULL);
	*i = 0;
	while (*i < 4)
		ft_lstclear(&list_arr[(*i)++], &none);
}

int	sort_words(t_list **words, t_list **argv, t_list **files, t_list **red)
{
	t_list	*tmp;

	tmp = *words;
	while (tmp)
	{
		if (*special_strchr(tmp->content, '>', NULL)
			|| *special_strchr(tmp->content, '<', NULL))
		{
			if (!tmp->next
				|| *special_strchr(tmp->next->content, '<', NULL)
				|| *special_strchr(tmp->next->content, '>', NULL))
				return (parse_error(FILE_ERR));
			safe_lstadd_back(red, tmp->content);
			tmp = tmp->next;
			safe_lstadd_back(files, tmp->content);
		}
		else
			safe_lstadd_back(argv, tmp->content);
		tmp = tmp->next;
	}
	if (check_redirections(*red))
		return (EXIT_FAILURE);
	words_processing(argv);
	words_processing(files);
	return (EXIT_SUCCESS);
}

int	init_token(t_token *token, char **words)
{
	t_list	*list_arr[4];
	int		code;

	ft_memset(list_arr, 0, 4 * sizeof(t_list *));
	while (*words)
		ft_lstadd_back(&list_arr[0], split_word(*(words++)));
	code = sort_words(&list_arr[0], &list_arr[1], &list_arr[2], &list_arr[3]);
	if (!code)
	{
		sort_and_fill(token, list_arr[2], list_arr[3], &code);
		code = 0;
		token->argv = (char **)list_to_array(list_arr[1], NULL);
		ft_lstclear(&list_arr[0], &none);
	}
	else
		ft_lstclear(&list_arr[0], &free);
	ft_lstclear(&list_arr[1], &none);
	ft_lstclear(&list_arr[2], &none);
	ft_lstclear(&list_arr[3], &none);
	return (code);
}

t_token	*parse_token(char *token_str)
{
	t_token	*token;
	char	**words;
	int		i;

	if (!check_spaces(token_str))
	{
		parse_error(PIPE_ERR);
		return (NULL);
	}
	words = special_split(token_str, ' ', NULL);
	token = safe_malloc(sizeof(t_token));
	i = 0;
	if (init_token(token, words))
	{
		free(token);
		token = NULL;
	}
	while (words[i])
	{
		free(words[i]);
		i++;
	}
	free(words);
	return (token);
}

t_token	**parse_input(char *input)
{
	t_token	**tokens;
	char	**token_strs;
	int		size;
	int		i;

	token_strs = special_split(input, '|', &size);
	tokens = safe_malloc((size + 1) * sizeof(t_token *));
	i = 0;
	while (token_strs[i])
	{
		tokens[i] = parse_token(token_strs[i]);
		if (!tokens[i++])
		{
			free_tokens(tokens);
			tokens = NULL;
			break ;
		}
	}
	if (tokens)
		tokens[size] = NULL;
	i = 0;
	while (token_strs[i])
		free(token_strs[i++]);
	free(token_strs);
	return (tokens);
}
