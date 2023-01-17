/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 12:48:57 by hoslim            #+#    #+#             */
/*   Updated: 2023/01/17 15:36:33 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//호출시 파이프 라인을 만들고 값을 넣어 실행?
//호출시 파이프를 구조체에 생성해 그 시그널 처리를 해주는 방식

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

void	hs_proc_child(t_cmd *cmd, int fd[2], char **envp)
{
	char	*path;
	char	**parse_cmd;
	char	**parse_envp;

	parse_envp = pipe_parsing_envp(envp);
	parse_cmd = ft_split(cmd->str, ' ');
	path = pipe_parsing_cmd(parse_envp, parse_cmd[0]);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	execve(path, parse_cmd, envp);
	hs_error_return(NULL, NULL, "Failed to execve\n");
}

void	hs_proc_parent(t_cmd *cmd, int fd[2], char **envp)
{
	char	*path;
	char	**parse_cmd;
	char	**parse_envp;

	parse_envp = pipe_parsing_envp(envp);
	parse_cmd = ft_split(cmd->str, ' ');
	path = pipe_parsing_cmd(parse_envp, parse_cmd[0]);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	execve(path, parse_cmd, envp);
	hs_error_return(NULL, NULL, "Failed to execve\n");
}

void	hs_pipeline(t_cmd *cmd, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		hs_error_return(NULL, cmd, "Failed to pipe");
	pid = fork();
	if (pid == -1)
		hs_error_return(NULL, cmd, "Failed to fork");
	else if (pid == 0)
		hs_proc_child(cmd->left, fd, envp);
	else
	{
		waitpid(pid, 0, WNOHANG);
		hs_proc_parent(cmd->right, fd, envp);
	}
}

void	hs_cmd(t_cmd *cur, char **envp)
{
	pid_t	pid;
	char	**parse_en;
	char	*path;
	char	**parse_cmd;

	pid = fork();
	if (pid == -1)
		hs_error_return(NULL, NULL, "Failed to fork\n");
	else if (pid == 0)
	{
		parse_en = pipe_parsing_envp(envp);
		parse_cmd = ft_split(cur->str, ' ');
		path = pipe_parsing_cmd(parse_en, parse_cmd[0]);
		execve(path, parse_cmd, envp);
		error(NULL, "Failed to execve\n");
	}
	else
		waitpid(pid, 0, 0);
}

void	hs_do_something(t_info *info)
{
	t_cmd	*cur;
	pid_t	pid;

	cur = info->cmd;
	if (cur->type == T_WORD)
		hs_cmd(cur, info->en);
	else if (cur->type == T_PIPE)
	{
		pid = fork();
		if (pid == -1)
			hs_error_return(NULL, NULL, "Failed to fork\n");
		else if (pid == 0)
			hs_pipeline(cur, info->en);
		else
			waitpid(pid, 0, 0);
	}
}
