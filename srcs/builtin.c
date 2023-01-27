/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 21:00:02 by hosunglim         #+#    #+#             */
/*   Updated: 2023/01/27 13:18:03 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	hs_exec_builtin(t_cmd *cmd, char **envp)
{
	if (!ft_strncmp(cmd->str, "env", 3))
		ft_env(cmd, envp);
	// else if (!ft_strncmp(cmd->str, "exit", 4))
	//     ft_exit(cmd);
	// else if (ft_strncmp(cmd->str, "cd", 2))
	// 	ft_cd(cmd, envp);
	// else if (ft_strncmp(cmd->str, "echo", 4))
	//     ft_echo(cmd, envp);
	else if (ft_strncmp(cmd->str, "unset", 5))
		ft_unset(cmd, envp);
	else if (!ft_strncmp(cmd->str, "pwd", 3))
		ft_pwd(cmd);
	else if (!ft_strncmp(cmd->str, "export", 6))
		ft_export(cmd, envp);
}

int	hs_check_builtin(t_cmd *cmd)
{
	if (!ft_strncmp(cmd->str, "cd", 2))
		return (1);
	else if (!ft_strncmp(cmd->str, "env", 3))
		return (1);
	else if (!ft_strncmp(cmd->str, "echo", 4))
		return (1);
	else if (!ft_strncmp(cmd->str, "unset", 5))
		return (1);
	else if (!ft_strncmp(cmd->str, "pwd", 3))
		return (1);
	else if (!ft_strncmp(cmd->str, "exit", 4))
		return (1);
	else if (!ft_strncmp(cmd->str, "export", 6))
		return (1);
	else
		return (0);
}
