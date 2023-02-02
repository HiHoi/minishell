/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 12:48:57 by hoslim            #+#    #+#             */
/*   Updated: 2023/02/02 20:21:18 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//sleep 커맨드는 waitpid가 0일때 제대로 기다림
//WNOH 옵션을 어떻게 써야 하는지 생각할 필요가 있음

extern	int	exit_code;

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

void	pipe_wait(pid_t pid)
{
	int	status;

	while (1)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			exit_code = WEXITSTATUS(status);
			return ;
		}
	}
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
		if (pid == -1)
			error(NULL, "Failed to fork\n");
		if (pid == 0 && cur->exec_flag == 0)
		{
			if (cur->right && cur->right->parent_flag == 1)
				pipe_word_p(fd[1], fd[0], cur->right, envp);
			else
				pipe_word(i, fd, cur, envp);
		}
		cur = cur->left;
	}
	pipe_wait(pid);
	exit(0);
}

void	hs_cmd(t_cmd *cmd, char ***envp)
{
	char	**parse_en;
	char	*path;
	char	**parse_cmd;

	if (cmd == NULL && cmd->exec_flag == 1)
		return ;
	if (hs_check_builtin(cmd))
		hs_exec_builtin(cmd, envp);
	if (cmd->type == T_REDI)
	{
		hs_redirect(cmd);
		// parse_cmd = ft_split(cmd->left->str, ' ');
	}
	// else
	// 	parse_cmd = ft_split(cmd->str, ' ');
	parse_cmd = hj_split_cmd(cmd->str, *envp);
	if (parse_cmd == NULL)
		exit(0);
	parse_en = pipe_parsing_envp(envp);
	path = pipe_parsing_cmd(parse_en, parse_cmd[0]);
	if (execve(path, parse_cmd, *envp) == -1)
		error(NULL, "Failed to execve\n");
}
