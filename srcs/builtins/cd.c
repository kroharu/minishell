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

static void	minus(t_info *info)
{
	char	*old_path;
	t_env	*pwd_node;
	t_env	*oldpwd_node;

	pwd_node = info->env_list;
	oldpwd_node = info->env_list;
	while (oldpwd_node && ft_strcmp(oldpwd_node->key, "OLDPWD", -1))
		oldpwd_node = oldpwd_node->next;
	if (!oldpwd_node || !oldpwd_node->value || !*oldpwd_node->value)
		error(ER_CDMINUS);
	old_path = ft_strdup(oldpwd_node->value);
	free(oldpwd_node->value);
	if (chdir(old_path) == -1)
		error(ER_CHDIR);
	printf("%s\n", old_path);
	while (pwd_node && ft_strcmp(pwd_node->key, "PWD", -1))
		pwd_node = pwd_node->next;
	if (pwd_node && pwd_node->value)
	{
		oldpwd_node->value = ft_strdup(pwd_node->value);
		free(pwd_node->value);
		pwd_node->value = ft_strdup(old_path);
	}
	else
		oldpwd_node->value = ft_strdup("");
	free(old_path);
}

int	cd(t_info *info, char **args)
{
	char	*path;

	if (!args[1] || ft_strcmp(args[1], "~", -1) == 0 || \
			ft_strcmp(args[1], "~/", -1) == 0)
		path = move_to_root(info);
	else
		path = args[1];
	if (ft_strcmp(path, "-", -1) == 0)
		minus(info);
	else if (chdir(path) != -1)
	{
		update_oldpwd(info);
		update_pwd(info);
	}
	else
		error(ER_CHDIR);
	return (0);
}
