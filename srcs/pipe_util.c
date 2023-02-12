/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:58:46 by hoslim            #+#    #+#             */
/*   Updated: 2023/02/10 15:31:06 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**pipe_parsing_envp(char ***envp)
{
	int		i;
	char	*path;
	char	**parsed_envp;

	if (*envp == NULL || hs_check_envp(envp, "PATH=") == 0)
		return (0);
	i = 0;
	while (ft_strncmp("PATH=", (*envp)[i], 5))
		i++;
	path = (*envp)[i] + 5;
	parsed_envp = ft_split(path, ':');
	return (parsed_envp);
}

char	*pipe_parsing_cmd(char **path, char *cmd)
{
	int		i;
	int		fd;
	char	*tmp;
	char	*cmd_path;

	if (!path || cmd == NULL || access(cmd, X_OK) != -1)
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

void	pipe_word(int prev[2], int now[2], t_cmd *cmd, char ***envp)
{
	t_cmd	*cur;

	cur = cmd;
	if (cmd->type == T_PIPE || prev == NULL)
		cur = cmd->left;
	hs_proc_child(cur, envp, prev, now);
}

void	close_other(int **fd, int cur, int count)
{
	int	idx;

	if (count == 1)
		return ;
	idx = 0;
	while (++idx < count + 1)
	{
		if (idx == cur || idx == cur - 1)
			continue ;
		else
		{
			close(fd[idx][0]);
			close(fd[idx][1]);
		}
	}
}

void	close_all(int **fd, int cur)
{
	int	idx;

	idx = 0;
	while (++idx < cur)
	{
		close(fd[idx][0]);
		close(fd[idx][1]);
	}
}
