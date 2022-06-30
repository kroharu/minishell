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

int	eof_detect(char *input)
{
	if (!input)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		return (1);
	}
	return (0);
}

//обработать < и > и ctrl+c в дочке минишелл

int	main(int argc, char **argv, char **envp)
{
	t_info	info;
	char	*input;

	(void)argc;
	(void)argv;
	init_info(&info, envp);
	g_info = &info;
	while (info.exit_flag == 0)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sigint_empty_handler);
		input = readline(PROMPT);
		if (eof_detect(input))
			break ;
		signal(SIGINT, sigint_handler_parent);
		if (input)
		{
			if (info.token && *(info.token))
				free_split(info.token);
			add_history(input);
			info.token = parse_input(input, &info);
			free(input);
			if (!g_info->exit_flag)
				execute(&info);
			else
				parse_error(g_info->exit_flag);
			/*printf("$? == %d\n", info.status);*/
		}
	}
	free_all(&info);
	return (info.status);
}
