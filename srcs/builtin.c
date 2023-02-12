/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 21:00:02 by hosunglim         #+#    #+#             */
/*   Updated: 2023/02/12 16:22:54 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	hs_exec_builtin(t_cmd *cmd, char ***envp)
{
	if (!ft_strncmp(cmd->str, "env", 3))
		ft_env(cmd, envp);
	else if (!ft_strncmp(cmd->str, "exit", 4) \
	&& !ft_strncmp(cmd->str, "(exit)", 6))
		ft_exit(cmd, envp);
	else if (!ft_strncmp(cmd->str, "cd", 2))
		ft_cd(cmd, envp);
	else if (!ft_strncmp(cmd->str, "echo", 4) || !ft_strncmp(cmd->str, "$?", 2))
		ft_echo(cmd, envp);
	else if (!ft_strncmp(cmd->str, "unset", 5))
		ft_unset(cmd, envp);
	else if (!ft_strncmp(cmd->str, "pwd", 3))
		ft_pwd(cmd);
	else if (!ft_strncmp(cmd->str, "export", 6))
		ft_export(cmd, envp);
	exit(0);
}

int	hs_check_builtin(t_cmd *cmd)
{
	if (cmd->str == NULL || cmd->type != T_WORD)
		return (0);
	if (!ft_strncmp(cmd->str, "cd", 2))
		return (1);
	else if (!ft_strncmp(cmd->str, "env", 3))
		return (1);
	else if (!ft_strncmp(cmd->str, "echo", 4))
		return (1);
	else if (!ft_strncmp(cmd->str, "$?", 2))
		return (1);
	else if (!ft_strncmp(cmd->str, "unset", 5))
		return (1);
	else if (!ft_strncmp(cmd->str, "pwd", 3))
		return (1);
	else if (!ft_strncmp(cmd->str, "exit", 4) \
	|| !ft_strncmp(cmd->str, "(exit)", 6))
		return (1);
	else if (!ft_strncmp(cmd->str, "export", 6))
		return (1);
	else
		return (0);
}

int	exec_builtin(t_cmd *cmd, char ***envp)
{
	if (cmd->type == T_WORD)
	{
		if (!ft_strncmp(cmd->str, "export", 6))
			ft_export(cmd, envp);
		else if (!ft_strncmp(cmd->str, "unset", 5))
			ft_unset(cmd, envp);
		else if (!ft_strncmp(cmd->str, "$?", 2))
			ft_echo(cmd, envp);
		else if (!ft_strncmp(cmd->str, "cd", 2))
			ft_cd(cmd, envp);
		else if (!ft_strncmp(cmd->str, "exit", 4) \
		|| !ft_strncmp(cmd->str, "(exit)", 6))
			ft_exit(cmd, envp);
		else
			return (1);
		return (0);
	}
	return (1);
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
		hs_redirect(cmd, envp);
		parse_cmd = hj_split_cmd(cmd->left->left->str, *envp);
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
