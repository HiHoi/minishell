/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:58:46 by hoslim            #+#    #+#             */
/*   Updated: 2023/02/07 22:04:50 by hoslim           ###   ########.fr       */
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

void	pipe_word(int parent[2], int child[2], t_cmd *cmd, char ***envp)
{
	if ((cmd->right == NULL && cmd->type == T_WORD) || cmd->type == T_REDI)
	{
		printf("c\n");
		hs_proc_child(cmd, envp, 0, parent);
	}
	else if (cmd->right && cmd->right->str && cmd->right->parent_flag == 0)
	{
		printf("c1\n");
		hs_proc_child(cmd->right, envp, child, parent);
	}
}

void	pipe_word_p(int close_fd[2], int open_fd[2], t_cmd *cmd, char ***envp)
{
	printf("p\n");
	if (close_fd != 0)
	{
		close(close_fd[0]);
		close(close_fd[1]);
	}
	hs_proc_parent(cmd, envp, open_fd);
}
