#include "minishell.h"

static int	envlist_len(t_env *env_list)
{
	t_env	*tmp;
	int		cnt;

	cnt = 0;
	tmp = env_list;
	while (tmp)
	{
		if (tmp->value)
			cnt++;
		tmp = tmp->next;
	}
	return (cnt);
}

void	update_shlvl(t_info *info)
{
	t_env	*tmp;
	char	*ptr;

	tmp = info->env_list;
	while (tmp && ft_strcmp(tmp->key, "SHLVL", -1))
		tmp = tmp->next;
	if (tmp)
	{
		ptr = tmp->value;
		tmp->value = ft_itoa(ft_atoi(tmp->value) + 1);
		free(ptr);
	}
}

void	update_envbin(t_info *info, char **token, int builtin)
{
	t_env   *tmp;

	tmp = info->env_list;
	while (tmp && ft_strcmp(tmp->key, "_", -1))
		tmp = tmp->next;
	if (tmp && token)
	{
		free(tmp->value);
		if (builtin >= 0)
			tmp->value = ft_strdup(token[0]);
		if (builtin < 0)
		{
			tmp->value = find_bin(info, token);
			if (!*tmp->value)
				tmp->value = ft_strdup(token[0]);
		}
	}
}

void	update_envp(t_info *info)
{
	int		cnt;
	int		i;
	t_env	*tmp;

	tmp = info->env_list;
	cnt = envlist_len(info->env_list);
	free_split(info->envp);
	info->envp = malloc(sizeof(char *) * (cnt + 1));
	if (!info->envp)
		error(ER_MALLOC);
	info->envp[cnt] = 0;
	i = 0;
	while (tmp && i < cnt)
	{
		if (tmp->key && tmp->value)
		{
			info->envp[i] = ft_strjoin(tmp->key, ft_strjoin("=", tmp->value, 0), 0);
			if (!info->envp[i++])
			{
				free_split(info->envp);
				error(ER_MALLOC);
			}
		}
		tmp = tmp->next;
	}
}
