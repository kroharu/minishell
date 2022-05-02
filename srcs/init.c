#include "minishell.h"

t_env	*init_env(char	**envp)
{
	t_env	*env_list;
	int		i;
	char	**split;

	i = -1;
	env_list = 0;
	while (envp[++i])
	{
		split = ft_split(envp[i], '=');
		env_list = ft_lstadd_back(env_list, \
				ft_lstnew(ft_strdup(split[0]), ft_strdup(split[1])));
		free(split[0]);
		free(split[1]);
		free(split);
		split = 0;
	}
	/*t_env	*tmp = env_list;*/
	/*printf("\n\n");*/
	/*while (tmp)*/
	/*{*/
		/*printf("%s=%s\n", tmp->key, tmp->value);*/
		/*tmp = tmp->next;*/
	/*}*/
	return (env_list);
}

char	**init_args(int argc, char **argv)
{
	int	i;
	char	**args;

	args = malloc(sizeof(char *)*(argc));
	if (!args)
		error(ER_MALLOC);
	args[argc - 1] = 0;
	i = 0;
	while (argv[++i])
		args[i - 1] = ft_strdup(argv[i]);
	return(args);
}

t_cmd	*init_cmd(char **token, int pipe_cnt)
{
	t_cmd   *cmd;
	int i;
	int start;
	int end;
	char **tmp;
	
	cmd = 0;
	start = -1;
	end = 0;
	while (pipe_cnt-- != -1)
	{
	    tmp = 0;
	    while (token[end] && ft_strcmp(token[end], "|", 0))
	        end++;
	    tmp = malloc(sizeof(char *)*(end - start));
	    if (!tmp)
	        error(ER_MALLOC);
	    i = -1;
	    while (++start < end)
	        tmp[++i] = ft_strdup(token[start]);
	    tmp[++i] = 0;
	    cmd = ft_cmdadd_back(cmd, ft_cmdnew(tmp));
	    end++;
	}
	return (cmd);
}
