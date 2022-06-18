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

static int	cnt_wrds(char **av)
{
	int	cnt;
	int	i;

	cnt = 0;
	i = -1;
	while (av && av[++i])
		cnt++;
	return (cnt);
}

static void	init_info(t_info *info, char **envp)
{
	info->exit_flag = 0;
	info->token = 0;
	info->envp = 0;
	info->cmd = 0;
	info->env_list = init_env(envp);
	update_envp(info);
	update_shlvl(info);
	init_builtins(info->builtins);
	init_blt_names(info->blt_names);
}

int	main(int argc, char **argv, char **envp)
{
	t_info	info;
	int		ac;
	char	**av;
	char	*tmp;

	(void)argc;
	(void)argv;
	init_info(&info, envp);
	/*signal(SIGABRT, catch_abrt);*/
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sigint_handler);
		write(1, PROMPT, ft_strlen(PROMPT));
		tmp = get_next_line(STDIN_FILENO);
		av = ft_split(tmp, ' ');
		ac = cnt_wrds(av) + 1;
		if (info.token && *(info.token))
			free_split(info.token);
		info.token = init_args(ac, av);
		free(tmp);
		free_split(av);
		execute(&info);
	}
	free_all(&info);
	return (0);
}
