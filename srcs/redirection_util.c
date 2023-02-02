/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:17:52 by hoslim            #+#    #+#             */
/*   Updated: 2023/02/02 19:18:25 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
