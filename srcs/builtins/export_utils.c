#include "minishell.h"

void	free_copy(char **copy)
{
	int	i;

	i = -1;
	while (copy && copy[++i])
		free(copy[i]);
	free(copy);
}

int	node_cnt(t_env *env_list)
{
	int	len;
	t_env	*tmp;

	len = 0;
	tmp = env_list;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

int	find_eq(char *arg)
{
	if (ft_strnstr(arg, "=", ft_strlen(arg)) || \
			ft_strnstr(arg, "+=", ft_strlen(arg)))
	{
		return (1);
	}
	return (0);
}

int	valid_args(char *args)
{
	int	i;

	i = -1;
	while (args[++i] && args[i] != '=')
	{
		if (!((args[i] >= 'A' && args[i] <= 'Z') || args[i] == '_' || \
					(args[i] >= 'a' && args[i] <= 'z') ||\
					(args[i] >= '0' && args[i] <= '9' && i != 0) || \
					(args[i] == '+' && args[i+1] && args[i+1] == '=')))
			return (0);
	}
	return (1);
}

t_env	*find_env(t_env *env_list, char *arg)
{
	t_env	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, arg, -1) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (0);
}
