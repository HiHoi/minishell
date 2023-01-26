/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:58:46 by hoslim            #+#    #+#             */
/*   Updated: 2023/01/26 12:59:20 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**pipe_parsing_envp(char **envp)
{
	char	*path;

	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	path = *envp + 5;
	return (ft_split(path, ':'));
}

char	*pipe_parsing_cmd(char **path, char *cmd)
{
	int		i;
	int		fd;
	char	*tmp;
	char	*cmd_path;

	if (access(cmd, X_OK) != -1)
		return (cmd);
	cmd_path = ft_strjoin("/", cmd);
	i = -1;
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], cmd_path);
		fd = access(tmp, X_OK);
		if (fd != -1)
		{
			free(cmd_path);
			return (tmp);
		}
		close(fd);
		free(tmp);
	}
	free(cmd_path);
	return (NULL);
}
