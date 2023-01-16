/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:09:15 by hoslim            #+#    #+#             */
/*   Updated: 2023/01/16 18:37:37 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**hs_parsing_envp(char **envp)
{
	char	*path;

	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	path = *envp + 5;
	return (ft_split(path, ':'));
}

char	*hs_parsing_cmd(char **path, char *cmd)
{
	int		i;
	int		fd;
	char	*cmd_path;
	char	*tmp;

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
			free(tmp);
			return (tmp);
		}
		close(fd);
		free(tmp);
	}
	free(cmd_path);
	return (NULL);
}

void	hs_proc_parent(t_info *info, char *str, int fd[2])
{
	char	**envp;
	char	*parsed_envp;
	char	**cmd;

	envp = hs_parsing_envp(info->en);
	parsed_envp = hs_parsing_cmd(envp, str);
	cmd = ft_split(str, ' ');
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	execve(parsed_envp, cmd, info->en);
	hs_error_return(info, "Failed to execve", 127);
}

void	hs_proc_child(t_info *info, char *str, int fd[2])
{
	char	**envp;
	char	*parsed_envp;
	char	**cmd;

	envp = hs_parsing_envp(info->en);
	parsed_envp = hs_parsing_cmd(envp, str);
	cmd = ft_split(str, ' ');
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	execve(parsed_envp, cmd, info->en);
	hs_error_return(info, "Failed to execve", 127);
}

void	hs_pipeline(t_info *info)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		hs_error_return(NULL, "Failed to pipe", 127);
	pid = fork();
	if (pid < 0)
		hs_error_return(NULL, "Failed to fork", 127);
	else if (pid == 0)
		hs_proc_child(info, info->cmd->left->str, fd);
	else
	{
		waitpid(pid, 0, WNOHANG);
		hs_proc_parent(info, info->cmd->str, fd);
	}
}
