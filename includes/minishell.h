#ifndef	MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>
#include <sys/dir.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <fcntl.h>

#include <limits.h>
# define DEF =
#define BUFFER_SIZE 100

#define PROMPT "💩$> "

#define ER_MALLOC 1
#define ER_EXECVE 2
#define ER_GETCWD 3
#define ER_CHDIR 4
#define ER_FORK 5
#define ER_ACCESS 6
#define ER_DIR 7
#define ER_OPEN 8
#define ER_DUP 9
#define ER_UNLINK 10

#define REDIR_IN 128
#define REDIR_OUT 129
#define REDIR_OUT_APP 130
#define HERE_DOC 131

#define FAIL 0
#define SUCCESS 1

typedef struct s_env
{
	char	*key;
	char	*value;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	char	**token;
	int		redir;
	int		redir_fd_in;
	int		redir_fd_out;
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
}	t_info;

typedef int (*t_builtins)(t_info *, char **);

int		pwd(t_info *info, char **args);
int		echo(t_info *info, char **args);
int		cd(t_info *info, char **args);
int		unset(t_info *info, char **args);
int		env(t_info *info, char **args);
int		ft_exit(t_info *info, char **args);
int 	export(t_info *info, char **args);
void	empty_args(t_env *env_list);
void	free_copy(char **copy);
int		node_cnt(t_env *env_list);
int		find_eq(char *arg);
int		valid_args(char **args);
int		check_env(t_env *env_list, char *arg);
void	error(int err_code);
int		ft_strlen(const char *str);
int		ft_strcmp(char *s1, char *s2, char ch);
int		ft_atoi(char *nptr);
char	*ft_itoa(int n);
int		ft_isspace(char *nptr);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char *s1, char *s2, int free_mode);
char	*ft_strnstr(char *haystack, char *needle, size_t len);
void	free_all(t_info *info);
void	free_split(char **split);
void	free_cmd(t_cmd *cmd);
t_env	*ft_lstlast(t_env *lst);
t_env	*ft_lstnew(char *key, char *value);
t_env	*ft_lstadd_back(t_env *lst, t_env *new_lst);
t_cmd	*ft_cmdlast(t_cmd *lst);
t_cmd	*ft_cmdnew(char **token);
t_cmd	*ft_cmdadd_back(t_cmd *lst, t_cmd *new_lst);
t_env	*init_env(char	**envp);
char	**init_args(int argc, char **argv);
t_cmd	*init_cmd(char **token, int pipe_cnt);
void	init_blt_names(char *blt_names[]);
void	init_builtins(void *builtins[]);
int		check_pipes(char **token);
int		find_builtin(t_info *info, char *token);
char	*find_bin(t_info *info, char **cmd);
void	execute(t_info *info);
void	check_redir(t_cmd **cmd);
void	update_shlvl(t_info *info);
void	update_envbin(t_info *info, char **token, int builtin);
void	update_envp(t_info *info);
void	dup_hub(t_cmd *cmd);
void	dup_back(int old_in, int old_out);
//gnl
char	*get_next_line(int fd);
int		find_n(char *s);
void	free_cache(char **s1);
void	cache_gen(char **buf, char **cache, int r);
char	*free_gnl(char **s1, char **s2);

#endif
