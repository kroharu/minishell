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
		write(1, "exit\n", 5);
		write(2, PROMPT, ft_strlen(PROMPT));
		write(2, ": exit:", 7);
		write(2, args[1], ft_strlen(args[1]));
		write(2, ": numeric argument required\n", 28);
		info->status = 255;
		exit(info->status);//switch to return
		return (info->status);
	}
	info->status = ft_atoi(args[1])%256;
	if (info->status < 0)
		info->status +=256;
	write(1, "exit\n", 5);
	info->exit_flag = 1;
	exit(info->status);//switch to return
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
		write(1, "exit\n", 5);
		info->exit_flag = 1;
		exit(0);//switch to return
	}
	else if (i == 2)
		return (one_arg(info, args));
	else
	{
		write(1, "exit\n", 5);
		write(2, PROMPT, ft_strlen(PROMPT));
		write(2, ": exit: too many arguments\n", 31);
		return (1);
	}
	return (0);
}
