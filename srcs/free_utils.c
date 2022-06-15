#include "minishell.h"

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd;
		if (cmd->token)
			free_split(cmd->token);
		cmd = cmd->next;
		free(tmp);
	}
}

void	free_all(t_info *info)
{
	t_env	*tmp;
	/*int		i;*/

	while (info->env_list)
	{
		if (info->env_list->key)
			free(info->env_list->key);
		if (info->env_list->value)
			free(info->env_list->value);
		tmp = info->env_list;
		info->env_list = info->env_list->next;
		free(tmp);
	}
	/*i = -1;*/
	/*while (info->token && info->token[++i])*/
		/*free(info->token[i]);*/
	/*free(info->token);*/
	free_split(info->token);
	free_split(info->envp);
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
