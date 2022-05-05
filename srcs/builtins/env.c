#include "minishell.h"

int	env(t_info *info, char **args)
{
	t_env	*tmp;

	(void)args;
	tmp = info->env_list;
	while (tmp)
	{
		if (tmp->key && tmp->value)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}
