#include "minishell.h"

static void	update_oldpwd(t_info *info)
{
	t_env	*tmp;
	char	*oldpwd;

	tmp = info->env_list;
	while (tmp && ft_strcmp(tmp->key, "PWD", -1))
		tmp = tmp->next;
	oldpwd = ft_strdup(tmp->value);
	tmp = info->env_list;
	while (tmp && ft_strcmp(tmp->key, "OLDPWD", -1))
		tmp = tmp->next;
	if (!tmp)
		info->env_list = ft_lstadd_back(info->env_list, \
				ft_lstnew("OLDPWD", oldpwd));
	else
	{
		free(tmp->value);
		tmp->value = oldpwd;
	}
}

static void	update_pwd(t_info *info)
{
	t_env	*tmp;
	char	*path;

	tmp = info->env_list;
	while (tmp && ft_strcmp(tmp->key, "PWD", -1))
		tmp = tmp->next;
	path = getcwd(0, 0);
	if (!path)
		error(ER_GETCWD);
	if (tmp->value)
		free(tmp->value);
	tmp->value = path;
}

static char	*move_to_root(t_info *info)
{
	char	*root;
	t_env	*tmp;

	tmp = info->env_list;
	while (tmp && ft_strcmp(tmp->key, "HOME", -1))
		tmp = tmp->next;
	if (!tmp)
		root = "/Users/cgoth";
	else
		root = tmp->value;
	return (root);
}

int	cd(t_info *info, char **args)
{
	char	*path;

	if (!args[1])
		path = move_to_root(info);
	else
		path = args[1];
	if (chdir(path) != -1)
	{
		update_oldpwd(info);
		update_pwd(info);
	}
	else
		error(ER_CHDIR);
	return (0);
}
