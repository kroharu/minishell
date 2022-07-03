#include "minishell.h"

static t_env	*del_node(t_env *root, t_env *node)
{
	t_env	*tmp;

	tmp = root;
	while (tmp && tmp != node && tmp->next != node)
		tmp = tmp->next;
	if (tmp != node)
		tmp->next = node->next;
	else
		root = node->next;
	free(node->key);
	free(node->value);
	free(node);
	return (root);
}

int	unset(t_info *info, char **args)
{
	t_env	*tmp;
	int		i;

	i = 0;
	while (args && args[++i])
	{
		if (!valid_args(args[i]))
		{
			error(ER_UNSET, "unset", args[i],\
				   ": not a valid identifier\n");
			info->status = 1;
		}
		else
		{
			tmp = find_env(info->env_list, args[i]);
			if (tmp)
				info->env_list = del_node(info->env_list, tmp);
		}
	}
	return (0);
}
