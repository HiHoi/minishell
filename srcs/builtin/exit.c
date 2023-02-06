/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:31:10 by hosunglim         #+#    #+#             */
/*   Updated: 2023/02/06 12:18:02 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	exit_code;

//parsing에서 $? 인식 필요

void	exit_get_code(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
}

//(exit)는 종료 되면 안됨

int	ft_exit(t_cmd *cmd, char ***envp)
{
	int		en_len;
	char	**parse;

	cmd->exec_flag = 1;
	parse = hj_split_cmd(cmd->str, *envp);
	if (ft_strncmp(parse[0], "exit", 4))
	{
		free_parse(parse);
		return (exit_code);
	}
	en_len = count_line(parse);
	if (en_len > 2)
	{
		write(2, "minishell: exit: too many argument\n", 35);
		exit_code = 1;
		free_parse(parse);
		return (exit_code);
	}
	exit_code = ft_atoi(parse[1]);
	write(1, "exit\n", 5);
	exit(exit_code);
}
