/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 12:48:57 by hoslim            #+#    #+#             */
/*   Updated: 2023/01/19 21:39:39 by hoslim           ###   ########.fr       */
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


void	hs_proc_child(t_cmd *cmd, char **envp, int parentfd[2], int fd[2])
{
	char	*path;
	char	**parse_cmd;
	char	**parse_envp;

	parse_envp = pipe_parsing_envp(envp);
	parse_cmd = ft_split(cmd->str, ' ');
	path = pipe_parsing_cmd(parse_envp, parse_cmd[0]);
	if (parentfd > 0)
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(parentfd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
		close(parentfd[1]);
		close(parentfd[0]);
	}
	else
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
	}
	execve(path, parse_cmd, envp);
	error(NULL, "Failed to execve\n");
}

void	hs_proc_parent(t_cmd *cmd, char **envp, int fd[2])
{
	char	*path;
	char	**parse_cmd;
	char	**parse_envp;

	parse_envp = pipe_parsing_envp(envp);
	parse_cmd = ft_split(cmd->str, ' ');
	path = pipe_parsing_cmd(parse_envp, parse_cmd[0]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	close(fd[0]);
	execve(path, parse_cmd, envp);
	error(NULL, "Failed to execve\n");
}

void	hs_pipeline(t_cmd *cmd, char **envp, int parent_fd[2])
{
	pid_t	pid;

	if (pipe(cmd->fd) == -1)
		hs_error_return(NULL, cmd, "Failed to pipe");
	pid = fork();
	if (pid == -1)
		hs_error_return(NULL, NULL, "Failed to fork");
	else if (pid == 0)
	{
		if (cmd->left->type == T_PIPE)
			hs_pipeline(cmd->left, envp, cmd->fd);
		else
			hs_proc_child(cmd->left, envp, 0, cmd->fd);
	}
	waitpid(pid, 0, WNOHANG);
	if (cmd->right->parent_flag == 1)
		hs_proc_parent(cmd->right, envp, cmd->fd);
	else
		hs_proc_child(cmd->right, envp, parent_fd, cmd->fd);
}

// void	hs_pipeline_main(t_cmd *cmd, char **envp)
// {
// 	pid_t	pid;

// 	pid = fork();
// 	if (pid == -1)
// 		hs_error_return(NULL, NULL, "Failed to fork\n");
// 	else if (pid == 0)
// 		hs_pipeline(cmd, envp);
// 	else
// 		waitpid(pid, 0, 0);
// }

void	hs_cmd(t_cmd *cmd, char **envp)
{
	char	**parse_en;
	char	*path;
	char	**parse_cmd;

	parse_en = pipe_parsing_envp(envp);
	parse_cmd = ft_split(cmd->str, ' ');
	path = pipe_parsing_cmd(parse_en, parse_cmd[0]);
	execve(path, parse_cmd, envp);
	error(NULL, "Failed to execve\n");
}

// void	hs_do_something(t_info *info)
// {
// 	t_cmd	*cur;
// 	pid_t	pid;

// 	cur = info->cmd;
// 	if (cur->type == T_WORD)
// 		hs_cmd(cur, info->en);
// 	else if (cur->type == T_PIPE)
// 	{
// 		pid = fork();
// 		if (pid == -1)
// 			hs_error_return(NULL, NULL, "Failed to fork\n");
// 		else if (pid == 0)
// 			hs_pipeline(cur, info->en);
// 		else
// 			waitpid(pid, 0, 0);
// 	}
// }

void	hs_excute_tree(t_cmd *cmd, char **envp)
{
	if (cmd->type == T_WORD)
		hs_cmd(cmd, envp);
	else if (cmd->type == T_PIPE)
		hs_pipeline(cmd, envp, 0);
	else if (cmd->type == T_REDI)
		hs_redirect(cmd);
}

void	hs_search_tree(t_cmd *cmd, char **envp)
{
	pid_t	pid;

	if (cmd->exec_flag == 1)
		return ;
	if (cmd->right && cmd->right->type != T_REDI)
		cmd->right->parent_flag = 1;
	pid = fork();
	if (pid < 0)
		hs_error_return(NULL, NULL, "Failed to fork\n");
	else if (pid == 0)
		hs_excute_tree(cmd, envp);
	else
		waitpid(pid, 0, 0);
	if (cmd->type == T_PIPE || cmd->type == T_REDI)
	{
		cmd->left->exec_flag = 1;
		cmd->right->exec_flag = 1;
	}
	if (cmd->left != NULL)
		hs_search_tree(cmd->left, envp);
	if (cmd->right != NULL)
		hs_search_tree(cmd->right, envp);
}
