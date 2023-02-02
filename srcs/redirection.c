/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:24:23 by hoslim            #+#    #+#             */
/*   Updated: 2023/02/02 18:43:12 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redi_input(t_cmd *cmd)
{
	int		in;
	char	*path;

	path = ft_strtrim(cmd->right->str, " ");
	in = open(path, O_RDONLY, 0644);
	if (in < 0)
		error(NULL, "Failed to open\n");
	dup2(in, STDIN_FILENO);
	close(in);
}

void	redi_output(t_cmd *cmd)
{
	int		out;
	char	*path;

	path = ft_strtrim(cmd->right->str, " ");
	out = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (out < 0)
		error(NULL, "Failed to open\n");
	dup2(out, STDOUT_FILENO);
	close(out);
}

char	*make_limiter(t_cmd *cmd)
{
	int		idx;
	int		len;
	char	*buf;
	char	*tmp;

	idx = hs_check_heredoc(cmd->str) + 1;
	len = 0;
	while (cmd->str[idx + len] != '|' && cmd->str[idx + len] != '>' \
	&& cmd->str[idx + len] != '<' && cmd->str[idx + len])
		len++;
	tmp = ft_substr(cmd->str, idx, len);
	buf = ft_strtrim(tmp, " ");
	free(tmp);
	return (buf);
}

void	make_temp(t_cmd *cmd)
{
	int		fd;
	char	*line;
	char	*limiter;

	limiter = make_limiter(cmd);
	fd = open(".temp_file", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		error(NULL, "Failed to open file");
	while (1)
	{
		line = readline("heredoc>");
		if (line == NULL || !ft_strcmp(line, limiter))
		{
			free(limiter);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	if (line)
		free(line);
	close(fd);
}

void	redi_heredoc(t_cmd *cmd)
{
	int		in;

	(void)cmd;
	in = open(".temp_file", O_RDONLY, 0644);
	if (in < 0)
		hs_error_return(NULL, NULL, "Failed to open\n");
	dup2(in, STDIN_FILENO);
	close(in);
}

void	redi_append(t_cmd *cmd)
{
	int		out;
	char	*path;

	path = ft_strtrim(cmd->right->str, " ");
	out = open(path, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (out < 0)
		error(NULL, "Failed to open\n");
	dup2(out, STDOUT_FILENO);
	close(out);
}

void	hs_redirect(t_cmd *cmd)
{
	int	i;

	i = -1;
	while (cmd->str[++i])
	{
		if (cmd->str[i] == '<')
		{
			if (cmd->str[i + 1] == '<')
				return (redi_heredoc(cmd));
			return (redi_input(cmd));
		}
		else if (cmd->str[i] == '>')
		{
			if (cmd->str[i + 1] == '>')
				return (redi_append(cmd));
			return (redi_output(cmd));
		}
	}
}
