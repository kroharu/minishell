/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladrian <ladrian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 17:57:14 by ladrian           #+#    #+#             */
/*   Updated: 2022/04/30 18:22:22 by ladrian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniparser.h"

void	init_term(void)
{
	struct termios	term;

	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(0, TCSANOW, &term);
	tgetent(0, getenv("TERM"));
}

int	check_spaces(char *str)
{
	int	i;

	i = -1;
	while (*(str + ++i))
	{
		if (*(str + i) != ' ')
			return (1);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	if (argc != 1)
		return (EXIT_FAILURE);
	g_data.exit_code = 0;
	copy_envp(envp);
	argv++;
	input = NULL;
	init_term();
	while (1)
	{
		input = get_input();
		if (input && check_spaces(input))
		{
			add_history(input);
			// exec(input); - твоё
		}
		free(input);
		input = NULL;
	}
	return (EXIT_SUCCESS);
}
