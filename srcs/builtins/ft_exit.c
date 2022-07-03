#include "minishell.h"

static int	is_num(char *str)
{
	int	i;

	i = ft_isspace(str);
	while (str && str[i])
	{
		if (!((str[i] >= '0' && str[i] <= '9') || str[i] == '-'))
			return (0);
		i++;
	}
	return (1);
}

static int	one_arg(t_info *info, char **args)
{
	if (!is_num(args[1]))
	{
		write(STDOUT_FILENO, "exit\n", 5);
		error(ER_EXIT, "exit", args[1],\
				": numeric argument required\n");
		info->status = 255;
		info->exit_flag = 1;
		return (info->status);
	}
	info->status = ft_atoi(args[1])%256;
	if (info->status < 0)
		info->status +=256;
	write(STDOUT_FILENO, "exit\n", 5);
	info->exit_flag = 1;
	return (info->status);
}

int	ft_exit(t_info *info, char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	if (i == 1)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		info->exit_flag = 1;
		return (0);
	}
	else if (i == 2)
		return (one_arg(info, args));
	else
	{
		write(STDOUT_FILENO, "exit\n", 5);
		error(ER_EXIT, "exit", 0, "too many arguments\n");
		return (1);
	}
	return (0);
}
