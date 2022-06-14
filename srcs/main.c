/*———————————No norme?——————————*/
/*⠀⣞⢽⢪⢣⢣⢣⢫⡺⡵⣝⡮⣗⢷⢽⢽⢽⣮⡷⡽⣜⣜⢮⢺⣜⢷⢽⢝⡽⣝*/
/*⠸⡸⠜⠕⠕⠁⢁⢇⢏⢽⢺⣪⡳⡝⣎⣏⢯⢞⡿⣟⣷⣳⢯⡷⣽⢽⢯⣳⣫⠇*/
/*⠀⠀⢀⢀⢄⢬⢪⡪⡎⣆⡈⠚⠜⠕⠇⠗⠝⢕⢯⢫⣞⣯⣿⣻⡽⣏⢗⣗⠏⠀*/
/*⠀⠪⡪⡪⣪⢪⢺⢸⢢⢓⢆⢤⢀⠀⠀⠀⠀⠈⢊⢞⡾⣿⡯⣏⢮⠷⠁⠀⠀ */
/*⠀⠀⠀⠈⠊⠆⡃⠕⢕⢇⢇⢇⢇⢇⢏⢎⢎⢆⢄⠀⢑⣽⣿⢝⠲⠉⠀⠀⠀⠀*/
/*⠀⠀⠀⠀⠀⡿⠂⠠⠀⡇⢇⠕⢈⣀⠀⠁⠡⠣⡣⡫⣂⣿⠯⢪⠰⠂⠀⠀⠀⠀*/
/*⠀⠀⠀⠀⡦⡙⡂⢀⢤⢣⠣⡈⣾⡃⠠⠄⠀⡄⢱⣌⣶⢏⢊⠂⠀⠀⠀⠀⠀⠀*/
/*⠀⠀⠀⠀⢝⡲⣜⡮⡏⢎⢌⢂⠙⠢⠐⢀⢘⢵⣽⣿⡿⠁⠁⠀⠀⠀⠀⠀⠀⠀*/
/*⠀⠀⠀⠀⠨⣺⡺⡕⡕⡱⡑⡆⡕⡅⡕⡜⡼⢽⡻⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀*/
/*⠀⠀⠀⠀⣼⣳⣫⣾⣵⣗⡵⡱⡡⢣⢑⢕⢜⢕⡝⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀*/
/*⠀⠀⠀⣴⣿⣾⣿⣿⣿⡿⡽⡑⢌⠪⡢⡣⣣⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀*/
/*⠀⠀⠀⡟⡾⣿⢿⢿⢵⣽⣾⣼⣘⢸⢸⣞⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀*/
/*⠀⠀⠀⠀⠁⠇⠡⠩⡫⢿⣝⡻⡮⣒⢽⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀*/
/*——————————————————————————————*/

#include "minishell.h"

void	free_all(t_info *info)
{
	t_env	*tmp;
	int		i;

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
	i = -1;
	while (info->token && info->token[++i])
		free(info->token[i]);
	free(info->token);
}

static int	cnt_wrds(char **av)
{
	int	cnt;
	int	i;

	cnt = 0;
	i = -1;
	while (av[++i])
		cnt++;
	return (cnt);
}

int	main(int argc, char **argv, char **envp)
{
	t_info	info;
	int		ac;
	char	**av;

	(void)argc;
	(void)argv;
	info.exit_flag = 0;
	info.token = 0;
	info.env_list = init_env(envp);
	update_envp(&info);
	update_shlvl(&info);
	init_builtins(info.builtins);
	init_blt_names(info.blt_names);
	while (1)
	{
		write(1, PROMPT, ft_strlen(PROMPT));
		av = ft_split(get_next_line(STDIN_FILENO), ' ');
		ac = cnt_wrds(av) + 1;
		if (info.token && *(info.token))
			free_split(info.token);
		info.token = init_args(ac, av);
		free_split(av);
		execute(&info);
	}
	free_all(&info);
	return (0);
}
