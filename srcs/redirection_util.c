/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:17:52 by hoslim            #+#    #+#             */
/*   Updated: 2023/02/12 15:52:46 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_exit_code;

char	*make_limiter(t_cmd *cmd)
{
	int		idx;
	int		len;
	char	*buf;
	char	*tmp;

	idx = hs_check_heredoc(cmd->str) + 1;
	len = 0;
	while (cmd->str[idx + len] && cmd->str[idx + len] != '|' \
	&& cmd->str[idx + len] != '>' && cmd->str[idx + len] != '<' \
	&& cmd->str[idx + len] != '\"')
		len++;
	tmp = ft_substr(cmd->str, idx, len);
	buf = ft_strtrim(tmp, " ");
	free(tmp);
	return (buf);
}

//heredoc 도중 들어오는 시그널 처리

void	handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_code = 1;
		rl_on_new_line();
		rl_redisplay();
	}
}

void	make_temp(t_cmd *cmd)
{
	int		fd;
	char	*line;
	char	*limiter;

	limiter = make_limiter(cmd);
	fd = open("/tmp/.temp_file", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		error(NULL, "Failed to open file\n", -1);
	g_exit_code = 0;
	while (1)
	{
		signal(SIGINT, handler_heredoc);
		line = readline("heredoc>");
		if (line == NULL || !ft_strcmp(line, limiter) || g_exit_code == 1)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	if (line)
		free(line);
	free(limiter);
	close(fd);
}

int	count_redi(t_cmd *cmd)
{
	t_cmd	*cur;
	int		count;

	cur = cmd;
	count = 0;
	while (cur)
	{
		if (cur->type == T_REDI)
			count++;
		cur = cur->right;
	}
	return (count);
}

void	redi_pipe(t_cmd *cmd, char ***envp)
{
	hs_redirect(cmd->left, envp);
	hs_redirect(cmd->right, envp);
	hs_cmd(cmd->left->left, envp);
}
