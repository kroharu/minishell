#include "minishell.h"

static int	redir_type(char *token)
{
	int	redir;

	redir = 0;
	if (ft_strcmp(token, ">", -1) == 0)
		redir = REDIR_OUT;
	if (ft_strcmp(token, ">>", -1) == 0)
		redir = REDIR_OUT_APP;
	if (ft_strcmp(token, "<", -1) == 0)
		redir = REDIR_IN;
	return (redir);
}

static void	open_file(t_cmd **cmd, char *file)
{
	t_cmd	*tmp;

	tmp = *cmd;
	if (tmp->redir == REDIR_OUT || tmp->redir == REDIR_OUT_APP)
	{
		if (tmp->redir_fd_out != STDOUT_FILENO)
			close(tmp->redir_fd_out);
		if (tmp->redir == REDIR_OUT)
			tmp->redir_fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			tmp->redir_fd_out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (tmp->redir_fd_out < 0)
			error(ER_OPEN);
	}
	if (tmp->redir == REDIR_IN)
	{
		if (tmp->redir_fd_in != STDIN_FILENO)
			close(tmp->redir_fd_in);
		tmp->redir_fd_in = open(file, O_RDONLY);
		if (tmp->redir_fd_in < 0)
			error(ER_OPEN);
	}
}

static int	redir_num(char **token)
{
	int	i;
	int	cnt;

	i = -1;
	cnt = 0;
	while (token[++i])
	{
		if (ft_strcmp(token[i], ">", -1) == 0 ||\
				ft_strcmp(token[i], ">>", -1) == 0 ||\
				ft_strcmp(token[i], "<", -1) == 0)
			cnt++;
	}
	return (cnt);
}

static char	**update_token(char **token)
{
	char	**new_token;
	int		i;
	int		j;

	i = 0;
	while (token[i])
		i++;
	new_token = malloc(sizeof(char *)*(i + 1 - 2*redir_num(token)));
	if (!new_token)
		error(ER_MALLOC);
	new_token[i - 2*redir_num(token)] = 0;
	i = 0;
	j = 0;
	while (token[i] && new_token[j])
	{
		//проверка на редирект и скип совпадений
		if (ft_strcmp(token[i], ">", -1) == 0 ||\
				ft_strcmp(token[i], ">>", -1) == 0 ||\
				ft_strcmp(token[i], "<", -1) == 0)
			i += 2;
		else
			new_token[j++] = ft_strdup(token[i++]);
	}
	free_split(token);
	return (new_token);
}

t_cmd	*check_redir(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	tmp = cmd;
	while (tmp)
	{
		i = -1;
		tmp->redir_fd_in = STDIN_FILENO;
		tmp->redir_fd_out = STDOUT_FILENO;
		while (tmp->token[++i] && tmp->token[i + 1])
		{
			tmp->redir = redir_type(tmp->token[i]);
			if (tmp->redir)
				open_file(&tmp, tmp->token[i + 1]); 
		}
		tmp->token = update_token(tmp->token);
		tmp = tmp->next;
	}
	return (cmd);
}
