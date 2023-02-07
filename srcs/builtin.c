/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 21:00:02 by hosunglim         #+#    #+#             */
/*   Updated: 2023/02/07 11:56:32 by hoslim           ###   ########.fr       */
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
	if (cmd->str == NULL)
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

void	exec_builtin(t_cmd *cmd, char ***envp)
{
	if (cmd->type == T_WORD)
	{
		if (!ft_strncmp(cmd->str, "export", 6))
			ft_export(cmd, envp);
		else if (!ft_strncmp(cmd->str, "unset", 5))
			ft_unset(cmd, envp);
		else if (!ft_strcmp(cmd->str, "$?"))
			ft_echo(cmd, envp);
		else if (!ft_strncmp(cmd->str, "cd", 2))
			ft_cd(cmd, envp);
		else if (!ft_strncmp(cmd->str, "exit", 4) \
		|| !ft_strncmp(cmd->str, "(exit)", 6))
			ft_exit(cmd, envp);
		return ;
	}
}
