#include "minishell.h"

int	check_pipes(char **token)
{
	int	i;
	int	pipe_cnt;

	i = -1;
	pipe_cnt = 0;
	while (token && token[++i])
	{
		if (!ft_strcmp(token[i], "|", 0))
			pipe_cnt++;
	}
	return (pipe_cnt);
}

int	find_builtin(t_info *info)
{
	(void)info;
	return (-1);
}

char	*find_bin(t_info *info, char **cmd)
{
	t_env	*tmp;
	char	*path;
	char	**split;
	int		i;

	tmp = info->env_list;
	while (tmp && ft_strcmp(tmp->key, "PATH", 0))
		tmp = tmp->next;
	split = ft_split(tmp->value, ':');
	i = -1;
	while (split[++i])
	{
		path = ft_strjoin(split[i], "/");
		path = ft_strjoin(path, cmd[0]);
		if (access(path, F_OK) == 0)
			return (path);
	}
	return (0);
}
