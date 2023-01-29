/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosunglim <hosunglim@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 12:48:57 by hoslim            #+#    #+#             */
/*   Updated: 2023/01/29 15:45:23 by hosunglim        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//sleep 커맨드는 waitpid가 0일때 제대로 기다림
//WNOH 옵션을 어떻게 써야 하는지 생각할 필요가 있음

void	hs_proc_child(t_cmd *cmd, char ***envp, int parentfd[2], int fd[2])
{
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
	hs_cmd(cmd, envp);
}

void	hs_proc_parent(t_cmd *cmd, char ***envp, int fd[2])
{
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	close(fd[0]);
	hs_cmd(cmd, envp);
}

void	hs_pipeline(t_cmd *cmd, char ***envp, int parent_fd[2])
{
	pid_t	pid;

	if (pipe(cmd->fd) == -1)
		error(NULL, "Failed to pipe\n");
	pid = fork();
	if (pid == -1)
		error(NULL, "Failed to fork\n");
	else if (pid == 0)
	{
		if (cmd->left->type == T_PIPE)
			hs_pipeline(cmd->left, envp, cmd->fd);
		else
			hs_proc_child(cmd->left, envp, 0, cmd->fd);
	}
	waitpid(pid, 0, 0);
	if (cmd->right->parent_flag == 1)
		hs_proc_parent(cmd->right, envp, cmd->fd);
	else
		hs_proc_child(cmd->right, envp, parent_fd, cmd->fd);
}

void	hs_cmd(t_cmd *cmd, char ***envp)
{
	char	**parse_en;
	char	*path;
	char	**parse_cmd;

	if (cmd->str == NULL)
		return ;
	if (hs_check_builtin(cmd))
		hs_exec_builtin(cmd, envp);
	if (cmd->type == T_REDI)
	{
		hs_redirect(cmd);
		parse_cmd = ft_split(cmd->left->str, ' ');
		parse_en = pipe_parsing_envp(envp);
		path = pipe_parsing_cmd(parse_en, parse_cmd[0]);
	}
	else
	{
		parse_cmd = ft_split(cmd->str, ' ');
		parse_en = pipe_parsing_envp(envp);
		path = pipe_parsing_cmd(parse_en, parse_cmd[0]);
	}
	unlink(".temp_file");
	execve(path, parse_cmd, *envp);
	error(NULL, "Failed to execve\n");
}

void	hs_excute_tree(t_cmd *cmd, char ***envp)
{
	if (cmd->type == T_PIPE)
		hs_pipeline(cmd, envp, 0);
	else
		hs_cmd(cmd, envp);
}

void	hs_search_tree(t_cmd *cmd, char ***envp)
{
	pid_t	pid;

	if (cmd->exec_flag == 1)
		return ;
	if (cmd->right)
		cmd->right->parent_flag = 1;
	pid = fork();
	if (pid < 0)
		error(NULL, "Failed to fork\n");
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
