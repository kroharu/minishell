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
	if (ft_strcmp(token, "<<", -1) == 0)
		redir = HERE_DOC;
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
	if (tmp->redir == REDIR_IN || tmp->redir == HERE_DOC)
	{
		if (tmp->redir_fd_in != STDIN_FILENO)
			close(tmp->redir_fd_in);
        if (tmp->redir == REDIR_IN)
		    tmp->redir_fd_in = open(file, O_RDONLY);
        else
            tmp->redir_fd_in = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
				ft_strcmp(token[i], "<<", -1) == 0 ||\
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
    int     cnt;

	i = 0;
	while (token[i])
		i++;
    cnt = redir_num(token);
	new_token = malloc(sizeof(char *)*(i + 1 - 2*cnt));
	if (!new_token)
		error(ER_MALLOC);
	new_token[i - 2*cnt] = 0;
	i = 0;
	j = 0;
	while (token[i])
	{
		//проверка на редирект и скип совпадений
		if (ft_strcmp(token[i], ">", -1) == 0 ||\
				ft_strcmp(token[i], ">>", -1) == 0 ||\
				ft_strcmp(token[i], "<<", -1) == 0 ||\
				ft_strcmp(token[i], "<", -1) == 0)
			i += 2;
		else
			new_token[j++] = ft_strdup(token[i++]);
	}
	free_split(token);
	return (new_token);
}

static void    fill_heredoc(t_cmd *cmd, char *eof)
{
    char    *tmp;

    if (cmd->redir_fd_in >= 0)
    {
        write(STDOUT_FILENO, "> ", 2);
        tmp = get_next_line(STDIN_FILENO);
        while (ft_strcmp(tmp, eof, -1))
        {
            tmp = ft_strjoin(tmp, "\n", 1);
            write(cmd->redir_fd_in, tmp, ft_strlen(tmp));
            free(tmp);
            write(STDOUT_FILENO, "> ", 2);
            tmp = get_next_line(STDIN_FILENO);
        }
		close(cmd->redir_fd_in);
		cmd->redir_fd_in = open("here_doc", O_RDONLY);
		if (cmd->redir_fd_in < 0)
			error(ER_OPEN);
    }
}

void	check_redir(t_cmd **cmd)
{
	t_cmd	*tmp;
	int		i;

	tmp = *cmd;
	while (tmp)
	{
		i = -1;
		tmp->redir_fd_in = STDIN_FILENO;
		tmp->redir_fd_out = STDOUT_FILENO;
		while (tmp->token[++i] && tmp->token[i + 1])
		{
			tmp->redir = redir_type(tmp->token[i]);
			if (tmp->redir)
            {
				open_file(&tmp, tmp->token[i + 1]);
                if (tmp->redir == HERE_DOC)
                    fill_heredoc(tmp, tmp->token[i + 1]);
            }
		}
		tmp->token = update_token(tmp->token);
		tmp = tmp->next;
	}
}
