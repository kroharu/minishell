#include "minishell.h"

int	find_builtin(t_info *info, char *token)
{
	int	i;

	i = -1;
	while (++i < 7)
	{
		if (ft_strcmp(token, info->blt_names[i], -1) == 0)
			return (i);
	}
	return (-1);
}

static int	dir_searcher(char *split, char *cmd)
{
	DIR	*dirp;
	struct dirent	*dp;

	dirp = opendir(split);
	if (!dirp)
		error(ER_DIR);
	dp = readdir(dirp);
	while (dp)
	{
		if (ft_strcmp(dp->d_name, cmd, -1) == 0)
		{
			closedir(dirp);
			return (SUCCESS);
		}
		dp = readdir(dirp);
	}
	closedir(dirp);
	return (FAIL);
}

/*char	*check_abspath(cmd)*/
/*{*/
	/*if (cmd[0] && (cmd[0][0] == '/' || cmd[0][0] =='.'))*/
	/*{*/
		/*if (access(cmd[0], F_OK) == 0)*/
			/*return (cmd[0]);*/
		/*error(ER_ACCESS);*/
	/*}*/
/*}*/

char	*find_bin(t_info *info, char **cmd)
{
	t_env	*tmp;
	char	*path;
	char	**split;
	int		i;

	if (!cmd || !cmd[0])
		return (0);
	if (cmd[0] && (cmd[0][0] == '/' || cmd[0][0] =='.'))
	{
		if (access(cmd[0], F_OK) == 0)
			return (cmd[0]);
		error(ER_ACCESS);
	}
	/*check_absapth(cmd);*/
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
