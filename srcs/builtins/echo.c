#include "minishell.h"

int	echo(t_info *info, char **args)
{
	int	n_flag;
	int	i;

	(void)info;
	n_flag = 0;
	if (args)
	{
		i = -1;
		if (!ft_strcmp(args[0], "-n", 0))
		{
			n_flag = 1;
			i++;
		}
		while (args && args[++i])
		{
			write(1, args[i], ft_strlen(args[i]));
			if (args[i + 1])
				write(1, " ", 1);
		}
		if (!n_flag)
			write(1, "\n", 1);
	}
	return (0);
}
