/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 21:00:02 by hosunglim         #+#    #+#             */
/*   Updated: 2023/02/14 18:49:18 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	hs_exec_builtin(t_cmd *cmd, char ***envp)
{
	char	**parse;

	parse = hj_split_cmd(cmd->str, *envp);
	if (!ft_strcmp(parse[0], "env"))
		ft_env(cmd, envp);
	else if (!ft_strcmp(parse[0], "exit") \
	&& !ft_strcmp(parse[0], "(exit)"))
		ft_exit(cmd, envp);
	else if (!ft_strcmp(parse[0], "cd"))
		ft_cd(cmd, envp);
	else if (!ft_strcmp(parse[0], "echo") || !ft_strcmp(parse[0], "$?"))
		ft_echo(cmd, envp);
	else if (!ft_strcmp(parse[0], "unset"))
		ft_unset(cmd, envp);
	else if (!ft_strcmp(parse[0], "pwd"))
		ft_pwd(cmd);
	else if (!ft_strcmp(parse[0], "export"))
		ft_export(cmd, envp);
	free_parse(parse);
	exit(0);
}

int	hs_check_builtin(t_cmd *cmd, char ***envp)
{
	char	**parse;
	int		ret;

	if (cmd->str == NULL || cmd->type != T_WORD)
		return (0);
	ret = 0;
	parse = hj_split_cmd(cmd->str, *envp);
	if (!ft_strcmp(parse[0], "cd"))
		ret = 1;
	else if (!ft_strcmp(parse[0], "env"))
		ret = 1;
	else if (!ft_strcmp(parse[0], "echo") || !ft_strcmp(parse[0], "$?"))
		ret = 1;
	else if (!ft_strcmp(parse[0], "unset"))
		ret = 1;
	else if (!ft_strcmp(parse[0], "pwd"))
		ret = 1;
	else if (!ft_strcmp(parse[0], "exit") \
	|| !ft_strcmp(parse[0], "(exit)"))
		ret = 1;
	else if (!ft_strcmp(parse[0], "export"))
		ret = 1;
	free_parse(parse);
	return (ret);
}

int	exec_builtin(t_cmd *cmd, char ***envp)
{
	char	**parse;

	if (cmd->type == T_WORD)
	{
		parse = hj_split_cmd(cmd->str, *envp);
		if (!ft_strcmp(parse[0], "export"))
			ft_export(cmd, envp);
		else if (!ft_strcmp(parse[0], "unset"))
			ft_unset(cmd, envp);
		else if (!ft_strcmp(parse[0], "$?"))
			ft_echo(cmd, envp);
		else if (!ft_strcmp(parse[0], "cd"))
			ft_cd(cmd, envp);
		else if (!ft_strcmp(parse[0], "exit") \
		|| !ft_strcmp(parse[0], "(exit)"))
			ft_exit(cmd, envp);
		else
		{
			free_parse(parse);
			return (1);
		}
		free_parse(parse);
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
	if (hs_check_builtin(cmd, envp))
		hs_exec_builtin(cmd, envp);
	if (cmd->type == T_REDI)
	{
		hs_redirect(cmd, envp);
		parse_cmd = hj_split_cmd(cmd->left->left->str, *envp);
	}
	else
		parse_cmd = hj_split_cmd(cmd->str, *envp);
	if (parse_cmd == NULL || (parse_cmd[0][0] == '\0' && parse_cmd[1] == NULL) \
	|| parse_cmd[0] == NULL)
		exit(0);
	parse_en = pipe_parsing_envp(envp);
	path = pipe_parsing_cmd(parse_en, parse_cmd[0]);
	if (execve(path, parse_cmd, *envp) == -1)
		error(NULL, parse_cmd[0], 2);
}
