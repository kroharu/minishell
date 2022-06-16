#include "minishell.h"

static void	check_add(char **arg, int *add_flag)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = *arg;
	while (tmp[i + 1])
		i++;
	if (tmp[i] == '+')
	{
		*add_flag = 1;
		tmp[i] = 0;
		/*tmp = malloc(sizeof(char *)*(i + 1));*/
		/*if (!tmp)*/
			/*error(ER_MALLOC);*/
		/*tmp[i] = 0;*/
		/*i = -1;*/
		/*while (tmp[++i])*/
			/*tmp[i] = arg[i];*/
		/*free(arg);*/
		/*return (tmp);*/
	}
	/*return(arg);*/
}

static void	new_var(t_info *info, char *arg)
{
	char	**split;
	int		add_flag;
	t_env	*tmp;

	add_flag = 0;
	split = ft_split(arg, '=');
	check_add(&(split[0]), &add_flag);
	if (find_env(info->env_list, split[0]) == 0)
	{
		info->env_list = ft_lstadd_back(info->env_list, \
				ft_lstnew(ft_strdup(split[0]), ft_strdup(split[1])));
	}
	else
	{
		tmp = info->env_list;
		while (ft_strcmp(split[0], tmp->key, -1))
			tmp = tmp->next;
		if (add_flag)
			tmp->value = ft_strjoin(tmp->value, split[1], 1);
		else
		{
			if (tmp->value)
				free(tmp->value);
			if (split[1])
				tmp->value = ft_strdup(split[1]);
			else
				tmp->value = ft_strdup("");
		}
	}
	/*free(split[0]);*/
	/*free(split[1]);*/
	/*free(split);*/
	free_split(split);
}

static void	parse_args(t_info *info, char **args)
{
	int	i;

	i = 0;
	while (args[++i])
	{
		if (!valid_args(args[i]))
		{
			write(2, "not a valid identifier\n", 23);
			info->status = 22;//EINVAL
		}
		else
		{
			if (find_eq(args[i]))
				new_var(info, args[i]);
			else
			{
				if (find_env(info->env_list, args[i]) == 0)
					info->env_list = ft_lstadd_back(info->env_list, \
							ft_lstnew(ft_strdup(args[i]), 0));
			}
		}
	}
}

int export(t_info *info, char **args)
{
	if (!args[1])
		empty_args(info->env_list);
	else
		parse_args(info, args);
	return (info->status);
}
