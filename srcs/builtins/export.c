#include "minishell.h"

char	*fill_copy(char *copy, t_env *tmp)
{
	int	i;
	int	j;

	i = -1;
	while (tmp->key[++i])
		copy[i] = tmp->key[i];
	if (tmp->value)
	{
		copy[i] = '=';
		copy[++i] = '"';
		if (*tmp->value)
		{
			j = -1;
			while (tmp->value[++j])
				copy[++i] = tmp->value[j];
		}
		copy[++i] = '"';
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

void	empty_args(t_env *env_list, int	eq_mode)
{
	int		i;
	int		len;
	char	**copy;

	len = node_cnt(env_list);
	copy = malloc(sizeof(char *)*(len + 1));
	if (!copy)
		error(ER_MALLOC);
	copy[len] = 0;
	i = -1;
	while (copy[++i] && tmp)
	{
		if (!tmp->value)
			copy[i] = malloc(sizeof(char *)*(ft_strlen(tmp->key)+1));
		else if (tmp->value && !*tmp->value)
			copy[i] = malloc(sizeof(char *)*(ft_strlen(tmp->key)+4));
		else
			copy[i] = malloc(sizeof(char *)*(ft_strlen(tmp->key)+ft_strlen(tmp->value)+4));
		if (!copy)
			error(ER_MALLOC);
		copy[i] = fill_copy(copy[i], tmp);
		tmp = tmp->next;
	}
}

int	func()
{
        if (!ft_strcmp(tmp->key, var, '='))
            cmp_flag = 1;
        tmp = tmp->next;
    }
    return (cmp_flag);
}

int split_eq(t_env **env_list, char *args, int eq_mode)
{
	char    **split;
	int     cmp_flag;
	t_env   *tmp;
	int     i;

	if (eq_mode == 2)
	    args = trim_first(args, '+');
	split = ft_split(args, '=');
	if (!split)
	    error(ER_MALLOC);
	cmp_flag = 0;
	tmp = *env_list;
	while (tmp && !cmp_flag) 
	{
		if (!ft_strcmp_export(tmp->var, split[0]))
		{
			cmp_flag = 1;
			break ;
		}
		tmp = tmp->next;
	}
	if (!cmp_flag)
	    *env_list = ft_lstadd_back(*env_list, ft_lstnew(ft_strdup(split[0]), ft_strdup(split[1])));
	else
	{
		if (eq_mode == 2)
			tmp->value = ft_strjoin(tmp->value, split[1]);
		else if (eq_mode == 1)
		{
			if (tmp->value)
				free(tmp->value);
			tmp->value = ft_strdup(split[1]);
		}
	}
	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
	free(args);
	return (0);
}

int export(t_info *info, char **args)
{
	int			i;
	static int	eq_mode = 0;

	/*i = -1;*/
	/*while (args[++i])*/
		/*printf("%s\n", args[i]);*/
	if (!args[1])
	{
		copy = empty_args(info->env_list, copy);
		eq_mode = 0;
	}
	else
	{
		if (!valid_args(args))
			error("not a valid identifier");
		i = 0;
		while (args[++i])
		{
			eq_mode = find_eq(args[i]);
			if (eq_mode)
				split_eq(&info->env_list, ft_strdup(args[i]), eq_mode);
			else
			{
				if (!check_var(info->env_list, args[i]))
					info->env_list = ft_lstadd_back(info->env_list, \
							ft_lstnew(ft_strdup(args[i]), 0));
			}
		}
	}
	return (0);
}
