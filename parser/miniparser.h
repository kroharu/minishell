/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniparser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladrian <ladrian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 15:17:19 by ladrian           #+#    #+#             */
/*   Updated: 2022/04/30 18:22:39 by ladrian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIPARSER_H
# define MINIPARSER_H

# define PROMPT "minishell-->"
# define QUOTE_ERR -1
# define PIPE_ERR -2
# define FILE_ERR -3
# define RED_ERR -4

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_data
{
	t_list		*envp;
	int			exit_code;
	pid_t		pid;
}			t_data;

t_data		g_data;

typedef struct s_token
{
	char	**argv;
	char	**in_files;
	char	**in_red;
	char	**out_files;
	char	**out_red;
}			t_token;

int		check_pipes(char *input);
int		check_special_chars(char *input);
char	*get_input(void);
void	push_word(t_list **words, char *start, char *end);
t_list	*get_words(char *line, char separator);
char	*special_strchr(char *line, char c, int *quote_flags);
char	**special_split(char *line, char separator, int *size);
int		ft_strcmp(const char *s1, const char *s2);
void	none(void *ptr);
void	append_str(char **s1, char *s2);
void	*safe_malloc(size_t size);
void	free_arr(char **arr);
t_list	*array_to_list(void **arr);
void	**list_to_array(t_list *list, int *arr_size);
void	print_list(void *content);
void	safe_lstadd_back(t_list **lst, void *content);
void	lst_remove(t_list **node, t_list *element);
int		parse_error(int code);
void	fatal_error(void);
void	sort_and_fill(t_token *token, t_list *files, t_list *red, int *i);
int		sort_words(t_list **words, t_list **argv, t_list **files, t_list **red);
int		init_token(t_token *token, char **words);
t_token	*parse_token(char *token_str);
t_token	**parse_input(char *input);
int		name_length(char *p);
char	*get_value(char *p, int len);
void	add_var(t_list **parts, char **start, char **p);
t_list	*get_word_parts(char *word);
void	parse_vars(char **word);
int		check_redirections(t_list *red);
void	trim_word(char **word);
void	words_processing(t_list **list);
t_list	*split_word(char *word);
int		check_spaces(char *str);
void	free_tokens(t_token **tokens);
void	ft_unsetenv(char *name);
void	ft_setenv(char *name, char *value);
char	*ft_getenv(char *name);
t_list	*find_var(char *name);
void	copy_envp(char **envp);

#endif