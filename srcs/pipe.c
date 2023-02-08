/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 12:48:57 by hoslim            #+#    #+#             */
/*   Updated: 2023/02/07 22:25:38 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_exit_code;

/*
void	hs_proc_child(t_cmd *cmd, char ***envp, int prev[2], int now[2])
{
	if (prev != 0)
	{
		dup2(prev[0], STDIN_FILENO);
		close(prev[0]);
		close(prev[1]);
	}
	if (now != 0)
	{
		dup2(now[1], STDOUT_FILENO);
		close(now[1]);
		close(now[0]);
	}
	hs_cmd(cmd, envp);
}

*/

void	hs_proc_child(t_cmd *cmd, char ***envp, int fd[2], int parentfd[2])
{
	if (fd != 0)
	{
		dup2(parentfd[0], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(parentfd[1]);
		close(parentfd[0]);
		close(fd[0]);
		close(fd[1]);
	}
	else
	{
		dup2(parentfd[1], STDOUT_FILENO);
		close(parentfd[1]);
		close(parentfd[0]);
	}
	hs_cmd(cmd, envp);
}

void	hs_proc_parent(t_cmd *cmd, char ***envp, int fd[2])
{
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	hs_cmd(cmd, envp);
}

void	pipe_wait(pid_t pid)
{
	int		status;

	while (1)
	{
		waitpid(pid, 0, 0);
		if (WIFEXITED(status))
		{
			g_exit_code = WEXITSTATUS(status);
			exit(g_exit_code);
		}
	}
}

int	count_pipe(t_cmd *cmd)
{
	int		i;
	t_cmd	*cur;

	i = 0;
	cur = cmd;
	while (cur->type == T_PIPE)
	{
		cur = cur->left;
		i++;
	}
	return (i);
}

int	**pipe_open(t_cmd *cmd)
{
	int	i;
	int	count;
	int	**ret;

	count = count_pipe(cmd);
	ret = malloc(sizeof(int *) * count);
	if (!ret)
		error(NULL, "Failed to malloc\n", -1);
	i = -1;
	while (++i < count)
	{
		ret[i] = malloc(sizeof(int [2]) * 1);
		if (!ret[i])
			error(NULL, "Failed to malloc\n", -1);
		if (pipe(ret[i]) < 0)
			error(NULL, "Failed to pipe\n", -1);
	}
	return (ret);
}

void	close_all(t_cmd *cmd, int **fd)
{
	int	idx;
	int	count;

	count = count_pipe(cmd);
	idx = -1;
	while (++idx < count)
	{
		close(fd[idx][0]);
		close(fd[idx][1]);
	}
}

/*
void	hs_pipeline(t_cmd *cmd, char ***envp)
{
	int		i;
	int		count;
	int		**fd;
	t_cmd	*cur;
	pid_t	pid;

	cur = cmd;
	fd = pipe_open(cmd);
	count = count_pipe(cmd);
	i = -1;
	while (cur && ++i < count)
	{
		pid = fork();
		if (pid == -1)
			error(NULL, "Failed to fork\n", -1);
		else if (pid == 0 && cur->exec_flag == 0)
		{
			if (i == 0)
				pipe_word(0, fd[i], cur->left, envp);
			else
				pipe_word(fd[i - 1], fd[i], cur, envp);
		}
		cur = cur->left;
	}
	close_all(cmd, fd);
	waitpid(pid, 0, 0);
	exit(0);
	// pipe_wait(pid);
}
*/

void	hs_pipeline(t_cmd *cmd, char ***envp)
{
	int		i;
	int		**fd;
	t_cmd	*cur;
	pid_t	pid;

	cur = cmd;
	fd = pipe_open(cmd);
	i = -1;
	while (cur && ++i > -1)
	{
		pid = fork();
		if (pid == -1)
			error(NULL, "Failed to fork\n", -1);
		else if ((pid == 0 && cur->exec_flag == 0))
		{
			if (cur->right && cur->right->parent_flag == 1)
				pipe_word_p(0, fd[i], cur->right, envp);
			else
				pipe_word(fd[i - 1], fd[i], cur, envp);
		}
		cur = cur->left;
	}
	close_all(cmd, fd);
	waitpid(pid, 0, 0);
	exit(0);
	// pipe_wait(pid);
}

void	hs_cmd(t_cmd *cmd, char ***envp)
{
	char	**parse_en;
	char	*path;
	char	**parse_cmd;

	if (cmd == NULL || cmd->exec_flag == 1)
		return ;
	if (hs_check_builtin(cmd))
		hs_exec_builtin(cmd, envp);
	if (cmd->type == T_REDI)
	{
		hs_redirect(cmd);
		parse_cmd = hj_split_cmd(cmd->left->str, *envp);
	}
	else
		parse_cmd = hj_split_cmd(cmd->str, *envp);
	if (parse_cmd == NULL || parse_cmd[0] == NULL)
		exit(0);
	parse_en = pipe_parsing_envp(envp);
	path = pipe_parsing_cmd(parse_en, parse_cmd[0]);
	if (execve(path, parse_cmd, *envp) == -1)
		error(NULL, parse_cmd[0], 2);
}
