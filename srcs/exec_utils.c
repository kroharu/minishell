#include "minishell.h"

int	check_pipes(char **token)
{
	int	i;
	int	pipe_cnt;

	i = -1;
	pipe_cnt = 0;
	while (token && token[++i])
	{
		if (ft_strcmp(token[i], "|", -1) == 0)
			pipe_cnt++;
	}
	return (pipe_cnt);
}
