/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:58:46 by hoslim            #+#    #+#             */
/*   Updated: 2023/02/03 13:54:57 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**pipe_parsing_envp(char ***envp)
{
	int		i;
	char	*path;

	i = 0;
	while (ft_strncmp("PATH", (*envp)[i], 4))
		i++;
	path = (*envp)[i] + 5;
	return (ft_split(path, ':'));
}

char	*pipe_parsing_cmd(char **path, char *cmd)
{
	int		i;
	int		fd;
	char	*tmp;
	char	*cmd_path;

	if (cmd == NULL || access(cmd, X_OK) != -1)
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

void	pipe_open(int fd[2][2])
{
	if (pipe(fd[0]) == -1)
		error(NULL, "Failed to pipe\n");
	if (pipe(fd[1]) == -1)
		error(NULL, "Failed to pipe\n");
}

void	pipe_word(int i, int fd[2][2], t_cmd *cmd, char ***envp)
{
	if ((cmd->right == NULL && cmd->type == T_WORD) || cmd->type == T_REDI)
	{
		if (i % 2 == 1)
		{
			close(fd[1][0]);
			close(fd[1][1]);
			hs_proc_child(cmd, envp, 0, fd[0]);
		}
		else
		{
			close(fd[0][0]);
			close(fd[0][1]);
			hs_proc_child(cmd, envp, 0, fd[1]);
		}
	}
	else if (cmd->right && cmd->right->parent_flag == 0)
	{
		if (i % 2 == 1)
			hs_proc_child(cmd->right, envp, fd[0], fd[1]);
		else
			hs_proc_child(cmd->right, envp, fd[1], fd[0]);
	}
}

void	pipe_word_p(int close_fd[2], int open_fd[2], t_cmd *cmd, char ***envp)
{
	close(close_fd[0]);
	close(close_fd[1]);
	hs_proc_parent(cmd, envp, open_fd);
}
