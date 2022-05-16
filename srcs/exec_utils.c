#include "minishell.h"

int	check_pipes(char **token)
{
	int	i;
	int	pipe_cnt;

	i = -1;
	pipe_cnt = 0;
	while (token && token[++i])
	{
		if (ft_strcmp(token[i], "|", -1) == 0)
			pipe_cnt++;
	}
	return (pipe_cnt);
}

int	find_builtin(t_info *info, char *token)
{
	int	i;

	i = -1;
	/*printf("%s\n", token);*/
	while (++i < 7)
	{
		/*printf("%d\n", i);*/
		if (ft_strcmp(token, info->blt_names[i], -1) == 0)
			return (i);
	}
	return (-1);
}

void	free_split(char **split)
{
	int	i;

	i = -1;
	if (split)
	{
		while (split[++i])
		{
			if (split[i])
				free(split[i]);
		}
		free(split);
	}
}

static int	dir_searcher(char *split, char *cmd)
{
	int	len;
	DIR	*dirp;
	struct dirent	*dp;

	dirp = opendir(split);
	if (!dirp)
		error(ER_DIR);
	len = ft_strlen(cmd);
	dp = readdir(dirp);
	while (dp)
	{
		if (dp->d_namlen == len && ft_strcmp(dp->d_name, cmd, -1) == 0)
		{
			closedir(dirp);
			return (SUCCESS);
		}
		dp = readdir(dirp);
	}
	closedir(dirp);
	return (FAIL);
}

char	*find_bin(t_info *info, char **cmd)
{
	t_env	*tmp;
	char	*path;
	char	**split;
	int		i;

	if (cmd[0] && cmd[0][0] == '/')
	{
		if (access(cmd[0], F_OK) == 0)
			return (cmd[0]);
		error(ER_ACCESS);
	}
	tmp = info->env_list;
	while (tmp && ft_strcmp(tmp->key, "PATH", -1) != 0)
		tmp = tmp->next;
	split = ft_split(tmp->value, ':');
	i = -1;
	while (split[++i])
	{
		if (dir_searcher(split[i], cmd[0]))
		{
			path = ft_strjoin(split[i], "/", 0);
			path = ft_strjoin(path, cmd[0], 1);
			free_split(split);
			return (path);
		}
	}
	free_split(split);
	return (0);
}
