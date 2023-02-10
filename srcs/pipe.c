/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 12:48:57 by hoslim            #+#    #+#             */
/*   Updated: 2023/02/10 23:25:03 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_exit_code;

void	hs_proc_child(t_cmd *cmd, char ***envp, int prev[2], int now[2])
{
	if (prev != 0)
	{
		close(prev[1]);
		dup2(prev[0], STDIN_FILENO);
		close(prev[0]);
	}
	if (now != 0)
	{
		close(now[0]);
		dup2(now[1], STDOUT_FILENO);
		close(now[1]);
	}
	hs_cmd(cmd, envp);
}

void	pipe_wait(int **fd, int count, t_cmd *cmd)
{
	int		status;
	t_cmd	*cur;

	cur = cmd;
	while (cur)
	{
		waitpid(cur->pid, &status, 0);
		if (WIFEXITED(status))
			g_exit_code = WEXITSTATUS(status);
		cur = cur->right;
	}
	free_fd(fd, count + 1);
	exit(g_exit_code);
}

int	count_pipe(t_cmd *cmd)
{
	int		i;
	t_cmd	*cur;

	i = 0;
	cur = cmd;
	while (cur->type == T_PIPE)
	{
		cur = cur->right;
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
	ret = malloc(sizeof(int *) * (count + 2));
	if (!ret)
		error(NULL, "Failed to malloc\n", -1);
	ret[0] = NULL;
	ret[count + 1] = NULL;
	i = 0;
	while (++i < count + 1)
	{
		ret[i] = malloc(sizeof(int [2]) * 1);
		if (!ret[i])
			error(NULL, "Failed to malloc\n", -1);
		if (pipe(ret[i]) < 0)
			error(NULL, "Failed to pipe\n", -1);
	}
	return (ret);
}

void	hs_pipeline(t_cmd *cmd, char ***envp)
{
	int		i;
	int		count;
	int		**fd;
	t_cmd	*cur;

	cur = cmd;
	fd = pipe_open(cmd);
	count = count_pipe(cmd);
	i = 0;
	while (cur && ++i < count + 2)
	{
		cur->pid = fork();
		if (cur->pid == -1)
			error(NULL, "Failed to fork\n", -1);
		else if (cur->pid == 0)
		{
			close_other(fd, i, count);
			pipe_word(fd[i - 1], fd[i], cur, envp);
		}
		cur = cur->right;
	}
	close_all(fd, count + 1);
	pipe_wait(fd, count, cmd);
}
