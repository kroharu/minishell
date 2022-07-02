#include "minishell.h"

int	pwd(t_info *info, char **args)
{
	char	*path;

	(void)info;
	(void)args;
	path = getcwd(0, 0);
	if (!path)
		error(ER_GETCWD, "getcwd", 0, 0);
	write(1, path, ft_strlen(path));
	write(1, "\n", 1);
	free(path);
	return (0);
}
