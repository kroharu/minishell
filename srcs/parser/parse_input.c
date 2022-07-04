/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladrian <ladrian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:33:59 by ladrian           #+#    #+#             */
/*   Updated: 2022/07/04 20:49:38 by cgoth            ###   ########.fr       */
/*                                                                            */
/*—————————————————————————————————No norme?——————————————————————————————————*/
/*                      ⠀⣞⢽⢪⢣⢣⢣⢫⡺⡵⣝⡮⣗⢷⢽⢽⢽⣮⡷⡽⣜⣜⢮⢺⣜⢷⢽⢝⡽⣝                        */
/*                      ⠸⡸⠜⠕⠕⠁⢁⢇⢏⢽⢺⣪⡳⡝⣎⣏⢯⢞⡿⣟⣷⣳⢯⡷⣽⢽⢯⣳⣫⠇                        */
/*                      ⠀⠀⢀⢀⢄⢬⢪⡪⡎⣆⡈⠚⠜⠕⠇⠗⠝⢕⢯⢫⣞⣯⣿⣻⡽⣏⢗⣗⠏⠀                        */
/*                      ⠀⠪⡪⡪⣪⢪⢺⢸⢢⢓⢆⢤⢀⠀⠀⠀⠀⠈⢊⢞⡾⣿⡯⣏⢮⠷⠁⠀⠀                         */
/*                      ⠀⠀⠀⠈⠊⠆⡃⠕⢕⢇⢇⢇⢇⢇⢏⢎⢎⢆⢄⠀⢑⣽⣿⢝⠲⠉⠀⠀⠀⠀                        */
/*                      ⠀⠀⠀⠀⠀⡿⠂⠠⠀⡇⢇⠕⢈⣀⠀⠁⠡⠣⡣⡫⣂⣿⠯⢪⠰⠂⠀⠀⠀⠀                        */
/*                      ⠀⠀⠀⠀⡦⡙⡂⢀⢤⢣⠣⡈⣾⡃⠠⠄⠀⡄⢱⣌⣶⢏⢊⠂⠀⠀⠀⠀⠀⠀                        */
/*                      ⠀⠀⠀⠀⢝⡲⣜⡮⡏⢎⢌⢂⠙⠢⠐⢀⢘⢵⣽⣿⡿⠁⠁⠀⠀⠀⠀⠀⠀⠀                        */
/*                      ⠀⠀⠀⠀⠨⣺⡺⡕⡕⡱⡑⡆⡕⡅⡕⡜⡼⢽⡻⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                        */
/*                      ⠀⠀⠀⠀⣼⣳⣫⣾⣵⣗⡵⡱⡡⢣⢑⢕⢜⢕⡝⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                        */
/*                      ⠀⠀⠀⣴⣿⣾⣿⣿⣿⡿⡽⡑⢌⠪⡢⡣⣣⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                        */
/*                      ⠀⠀⠀⡟⡾⣿⢿⢿⢵⣽⣾⣼⣘⢸⢸⣞⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                        */
/*                      ⠀⠀⠀⠀⠁⠇⠡⠩⡫⢿⣝⡻⡮⣒⢽⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                        */
/* ************************************************************************** */

#include "minishell.h"

char	**parse_input(char *input, t_info *info)
{
	t_parser	parser;
	char		*pre_input;
	int			i;

	pre_input = split_pipes(input);
	parser.input = special_split(pre_input, ' ', &i);
	free(pre_input);
	if (parser.input)
		parser.input[i] = NULL;
	g_info->parse_status = error_handler(parser.input, i);
	pre_find_envp(&parser, info);
	parser.token = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (parser.input[++i])
		ft_trim_qoutes(&parser, i);
	parser.token[i] = NULL;
	free_split(parser.input);
	parser.input = NULL;
	return (parser.token);
}

void	ft_trim_qoutes(t_parser *parser, int i)
{
	int	j;
	int	k;
	int	flag;

	flag = 1;
	parser->token[i] = malloc(sizeof(char)
			* (ft_strlen(parser->input[i]) + 1));
	k = -1;
	j = -1;
	if (parser->input[i][0] == '\"' || parser->input[i][0] == '\'')
	{
		flag = -1;
		j++;
	}
	if (flag == 1)
		while (parser->input[i][++j])
			parser->token[i][++k] = parser->input[i][j];
	else
		while (parser->input[i][++j + 1])
			parser->token[i][++k] = parser->input[i][j];
	k++;
	parser->token[i][k] = '\0';
}

char	**special_split(char *line, char separator, int *size)
{
	t_list	*words;
	char	**arr;

	words = get_words(line, separator);
	arr = (char **)list_to_array(words, size);
	ft_lstclear(&words, &none);
	return (arr);
}
