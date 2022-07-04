/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladrian <ladrian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 17:19:38 by cgoth             #+#    #+#             */
/*   Updated: 2022/07/04 17:58:10 by ladrian          ###   ########.fr       */
/*                                                                            */
/*—————————————————————————————————No norme?——————————————————————————————————*/
/*                      ⠀⣞⢽⢪⢣⢣⢣⢫⡺⡵⣝⡮⣗⢷⢽⢽⢽⣮⡷⡽⣜⣜⢮⢺⣜⢷⢽⢝⡽⣝                    */
/*                      ⠸⡸⠜⠕⠕⠁⢁⢇⢏⢽⢺⣪⡳⡝⣎⣏⢯⢞⡿⣟⣷⣳⢯⡷⣽⢽⢯⣳⣫⠇                    */
/*                      ⠀⠀⢀⢀⢄⢬⢪⡪⡎⣆⡈⠚⠜⠕⠇⠗⠝⢕⢯⢫⣞⣯⣿⣻⡽⣏⢗⣗⠏⠀                    */
/*                      ⠀⠪⡪⡪⣪⢪⢺⢸⢢⢓⢆⢤⢀⠀⠀⠀⠀⠈⢊⢞⡾⣿⡯⣏⢮⠷⠁⠀⠀                     */
/*                      ⠀⠀⠀⠈⠊⠆⡃⠕⢕⢇⢇⢇⢇⢇⢏⢎⢎⢆⢄⠀⢑⣽⣿⢝⠲⠉⠀⠀⠀⠀                    */
/*                      ⠀⠀⠀⠀⠀⡿⠂⠠⠀⡇⢇⠕⢈⣀⠀⠁⠡⠣⡣⡫⣂⣿⠯⢪⠰⠂⠀⠀⠀⠀                    */
/*                      ⠀⠀⠀⠀⡦⡙⡂⢀⢤⢣⠣⡈⣾⡃⠠⠄⠀⡄⢱⣌⣶⢏⢊⠂⠀⠀⠀⠀⠀⠀                    */
/*                      ⠀⠀⠀⠀⢝⡲⣜⡮⡏⢎⢌⢂⠙⠢⠐⢀⢘⢵⣽⣿⡿⠁⠁⠀⠀⠀⠀⠀⠀⠀                    */
/*                      ⠀⠀⠀⠀⠨⣺⡺⡕⡕⡱⡑⡆⡕⡅⡕⡜⡼⢽⡻⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                    */
/*                      ⠀⠀⠀⠀⣼⣳⣫⣾⣵⣗⡵⡱⡡⢣⢑⢕⢜⢕⡝⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                    */
/*                      ⠀⠀⠀⣴⣿⣾⣿⣿⣿⡿⡽⡑⢌⠪⡢⡣⣣⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                    */
/*                      ⠀⠀⠀⡟⡾⣿⢿⢿⢵⣽⣾⣼⣘⢸⢸⣞⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                    */
/*                      ⠀⠀⠀⠀⠁⠇⠡⠩⡫⢿⣝⡻⡮⣒⢽⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                    */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/errno.h>
# include <sys/dir.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include <fcntl.h>
# include <signal.h>

# include <readline/readline.h>
# include <readline/history.h>

# include <limits.h>
# define DEF =
# define BUFFER_SIZE 100

# define PROMPT "💩$> "
# define PROMPT_ERR "💩: "
# define HD "here_doc"

# define QUOTE_ERR -1
# define PIPE_ERR -2
# define REDIR_ERR -3

# define ER_MALLOC 1
# define ER_EXECVE 2
# define ER_GETCWD 3
# define ER_CHDIR 4
# define ER_FORK 5
# define ER_ACCESS 6
# define ER_DIR 7
# define ER_OPEN 8
# define ER_DUP 9
# define ER_UNLINK 10
# define ER_CDMINUS 11
# define ER_CMDNOTFND 12
# define ER_CMDDIR 13
# define ER_EXPORT 14
# define ER_EXIT 15
# define ER_UNSET 16

# define REDIR_IN 128
# define REDIR_OUT 129
# define REDIR_OUT_APP 130
# define HERE_DOC 131

# define FAIL 0
# define SUCCESS 1

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_parser
{
	char	**token;
	char	**input;
}	t_parser;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	char			**token;
	int				redir;
	int				redir_fd_in;
	int				redir_fd_out;
	int				pipefd[2];
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_info
{
	t_env	*env_list;
	t_cmd	*cmd;
	char	**envp;
	char	**token;
	void	*builtins[7];
	char	*blt_names[7];
	int		status;
	int		exit_flag;
	int		parse_status;
}	t_info;

t_info			*g_info;

typedef int		(*t_builtins)(t_info *, char **);
extern void		rl_replace_line(const char *a, int b);

int				pwd(t_info *info, char **args);
int				echo(t_info *info, char **args);
int				cd(t_info *info, char **args);
int				unset(t_info *info, char **args);
int				env(t_info *info, char **args);
int				ft_exit(t_info *info, char **args);
int				export(t_info *info, char **args);
void			empty_args(t_env *env_list);
void			free_copy(char **copy);
int				node_cnt(t_env *env_list);
int				find_eq(char *arg);
int				valid_args(char *args);
t_env			*find_env(t_env *env_list, char *arg);
void			error(int err_code, char *cmd, char *input, char *text);
void			error_exit(int code);
int				ft_strlen(const char *str);
int				ft_strcmp(char *s1, char *s2, char ch);
int				ft_atoi(char *nptr);
char			*ft_itoa(int n);
int				ft_isspace(char *nptr);
char			**ft_split(char const *s, char c);
char			*ft_strdup(const char *s1);
char			*ft_strjoin(char *s1, char *s2, int free_mode);
char			*ft_strnstr(char *haystack, char *needle, size_t len);
void			free_all(t_info *info);
void			free_split(char **split);
void			free_cmd(t_cmd *cmd);
t_env			*ft_lstlast(t_env *lst);
t_env			*ft_lstnew(char *key, char *value);
t_env			*ft_lstadd_back(t_env *lst, t_env *new_lst);
t_cmd			*ft_cmdlast(t_cmd *lst);
t_cmd			*ft_cmdnew(char **token);
t_cmd			*ft_cmdadd_back(t_cmd *lst, t_cmd *new_lst);
t_env			*init_env(char	**envp);
t_cmd			*init_cmd(char **token, int pipe_cnt);
void			init_blt_names(char *blt_names[]);
void			init_builtins(void *builtins[]);
int				check_pipes(char **token);
int				ft_arrlen(char	**arr);
int				redir_num(char **token);
int				find_builtin(t_info *info, char *token);
char			*find_bin(t_info *info, char **cmd);
void			execute(t_info *info);
void			exec_solocmd(t_info *info, t_cmd *cmd);
void			multiple_pipe(t_info *info, t_cmd *cmd);
void			exec_cmd(t_info *info, t_cmd *cmd);
void			get_status(t_info *info);
void			check_redir(t_cmd **cmd);
void			update_shlvl(t_info *info);
void			update_envbin(t_info *info, char **token);
void			update_envp(t_info *info);
void			dup_hub(t_cmd *cmd);
void			dup_back(int old_in, int old_out);
void			sigquit_handler_child(int signum);
void			sigint_empty_handler(int signum);
void			sigint_handler_parent(int signum);
void			sigquit_handler_parent(int signum);

char			*loop(char *arr, t_env *lst, t_info *info);
char			**parse_input(char *input, t_info *info);
void			find_envp(t_parser *parser, int envp, t_info *info);
int				find_dollar(char *str);
char			**special_split(char *line, char separator, int *size);
void			none(void *ptr);
t_list			*get_words(char *line, char separator);
char			*special_strchr(char *line, char c, int *quote_flags);
void			push_word(t_list **words, char *start, char *end);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
t_list			*ft_mylstnew(void *content);
void			**list_to_array(t_list *list, int *arr_size);
int				ft_lstsize(t_list *lst);
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			free_tokens(char **tokens);
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			*safe_malloc(size_t size);
void			fatal_error(void);
void			ft_mylstadd_back(t_list **lst, t_list *new);
t_list			*ft_mylstlast(t_list *lst);
void			pre_find_envp(t_parser *parser, t_info *info);
void			ft_trim_qoutes(t_parser *parser, int i);
char			*envp_with_symbols(char *str, char *value, char *key);
void			parse_error(int error);
int				error_handler(char **input, int num);
int				pipe_checker(char **input, int num);
void			ft_putendl_fd(char *s, int fd);
void			ft_putstr_fd(char *s, int fd);
int				find_pipe(char *token);
int				ft_isdigit(int c);
int				ft_isalpha(int c);
int				find_reverse_pipe(char *token);
char			*split_pipes(char *input);
int				pipe_count(char *input, int *i);
char			*empty_envp_key(char *str);
char			*empty_envp(char *str, char *value, char *key);
int				cmp_key(char *str, char *key);
int				quote_checker(char **input);
int				redir_checker(char **input);
int				find_start_of_envp(int *j, int k, char *str);
char			*rewrite_token(char *str, t_env *lst, t_info *info);

#endif
