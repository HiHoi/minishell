/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 12:36:41 by hoslim            #+#    #+#             */
/*   Updated: 2023/02/14 14:51:36 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_exit_code;

int	syntax_pipe(t_cmd *cmd)
{
	if (cmd->left && cmd->left->str && cmd->right && cmd->right->str)
		return (1);
	return (-1);
}

int	syntax_redi(t_cmd *cmd)
{
	if (hs_check_heredoc(cmd->str))
		return (1);
	if (cmd->right && cmd->right->str == NULL)
		return (-1);
	return (1);
}

int	syntax_word(t_cmd *cmd)
{
	if (cmd->str == NULL)
		return (1);
	if (ft_strchr(cmd->str, '`') || hj_compare_check(cmd->str) == 0)
		return (-1);
	return (1);
}

int	check_cmd_syntax(t_cmd *cmd, char ***envp)
{
	int	ret;

	ret = 1;
	if (cmd->type == T_PIPE)
		ret = syntax_pipe(cmd);
	else if (cmd->type == T_REDI)
		ret = syntax_redi(cmd->left);
	else if (cmd->type == T_WORD)
		ret = syntax_word(cmd);
	if (cmd->left != NULL && ret == 1)
		ret = check_cmd_syntax(cmd->left, envp);
	if (cmd->right != NULL && ret == 1)
		ret = check_cmd_syntax(cmd->right, envp);
	return (ret);
}

int	check_cmd_exec(t_cmd *cmd, char ***envp)
{
	if (check_cmd_syntax(cmd, envp) == -1)
	{
		write(2, "minishell: ", 12);
		write(2, cmd->str, ft_strlen(cmd->str));
		write(2, ": syntax error\n", 16);
		g_exit_code = 258;
		return (g_exit_code);
	}
	if (hs_check_builtin(cmd, envp) == 1)
		return (-1);
	return (-1);
}
