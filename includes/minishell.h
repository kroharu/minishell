#ifndef	MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>

#define PROMPT "💩"
#define ER_MALLOC 1
#define ER_EXECVE 2
#define ER_GETCWD 3
#define ER_CHDIR 4
#define ER_FORK 5

typedef struct s_env
{
	char	*key;
	char	*value;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	char	**token;
	struct s_cmd	*next;
}	t_cmd;

//typedef struct s_export
//{
	//char	**env_arr;
	//t_env	*env_list
//}	t_export;

typedef struct s_info
{
	t_env	*env_list;
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
int		ft_isspace(char *nptr);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strnstr(char *haystack, char *needle, size_t len);
void	free_all(t_info *info);
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

#endif
