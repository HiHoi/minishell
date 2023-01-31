/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 12:48:57 by hoslim            #+#    #+#             */
/*   Updated: 2023/01/31 17:12:07 by hoslim           ###   ########.fr       */
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
	exit(0);
}

void	hs_proc_parent(t_cmd *cmd, char ***envp, int fd[2])
{
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	hs_cmd(cmd, envp);
	exit(0);
}

void	hs_pipeline(t_cmd *cmd, char ***envp)
{
	int		i;
	int		fd[2][2];
	t_cmd	*cur;
	pid_t	pid;

	pipe_open(fd);
	cur = cmd;
	i = -1;
	while (cur && ++i > -1)
	{
		pid = fork();
		if (pid == 0)
		{
			if (cur->right == NULL && cur->type == T_WORD)
				pipe_word(i, fd, cur, envp);
			else if (cur->right && cur->right->parent_flag == 1)
				pipe_word_p(fd[1], fd[0], cur->right, envp);
			else if (cur->right && cur->right->parent_flag == 0)
				pipe_word(i, fd, cur, envp);
		}
		cur = cur->left;
	}
	waitpid(pid, 0, WNOHANG);
	exit(0);
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
	if (execve(path, parse_cmd, *envp) == -1)
		error(NULL, "Failed to execve\n");
	exit(0);
}

void	hs_excute_tree(t_cmd *cmd, char ***envp)
{
	if (cmd->type == T_PIPE)
		hs_pipeline(cmd, envp);
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
