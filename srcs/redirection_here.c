/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_here.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:56:49 by hoslim            #+#    #+#             */
/*   Updated: 2023/02/13 16:58:02 by hoslim           ###   ########.fr       */
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

void	handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		g_exit_code = 1;
		exit(g_exit_code);
	}
}

void	wait_heredoc(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	g_exit_code = WEXITSTATUS(status);
}

void	proc_heredoc(int fd, char *limiter)
{
	pid_t	pid;
	char	*line;

	pid = fork();
	if (pid < 0)
		error(NULL, "Failed to fork\n", -1);
	else if (pid == 0)
	{
		while (1)
		{
			signal(SIGINT, handler_heredoc);
			line = readline("heredoc>");
			if (line == NULL || !ft_strcmp(line, limiter))
				break ;
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
			free(line);
		}
		if (line)
			free(line);
		exit(0);
	}
	wait_heredoc(pid);
}

void	make_temp(t_cmd *cmd)
{
	int		fd;
	char	*limiter;

	g_exit_code = 0;
	limiter = make_limiter(cmd);
	fd = open("/tmp/.temp_file", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		g_exit_code = 1;
		hs_error_return(NULL, NULL, "Failed to open file\n");
	}
	proc_heredoc(fd, limiter);
	free(limiter);
	close(fd);
}
