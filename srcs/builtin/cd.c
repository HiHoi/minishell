/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 20:36:20 by hosunglim         #+#    #+#             */
/*   Updated: 2023/02/06 13:32:52 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	exit_code;

char	*cd_parse_path(char *cmd, char ***envp)
{
	char	*want;
	char	*pwd;
	char	*path;
	char	**parse;

	parse = ft_split(cmd, ' ');
	pwd = parse_env_value("PWD", envp);
	path = ft_strjoin("/", parse[1]);
	want = ft_strjoin(pwd, path);
	free_parse(parse);
	free(pwd);
	free(path);
	return (want);
}

void	cd_oldpwd(char ***envp)
{
	char	*cur;
	char	*old;
	char	*buf;

	buf = parse_env_value("PWD", envp);
	old = ft_strjoin("OLDPWD=", buf);
	swap_env(envp, old, "OLDPWD");
	free(buf);
	buf = getcwd(NULL, 1024);
	cur = ft_strjoin("PWD=", buf);
	swap_env(envp, cur, "PWD");
	free(buf);
	free(old);
	free(cur);
}

void	cd_home(char ***envp)
{
	char	*path;

	path = parse_env_value("HOME", envp);
	if (chdir(path) == -1)
	{
		exit_code = 127;
		return ;
	}
}

void	ft_cd(t_cmd *cmd, char ***envp)
{
	char	**parse;
	char	*want_path;

	cmd->exec_flag = 1;
	parse = ft_split(cmd->str, ' ');
	want_path = cd_parse_path(cmd->str, envp);
	if (ft_strcmp(parse[0], "cd"))
	{
		exit_code = 127;
		return ;
	}
	if (parse[1] != NULL && parse[1][0] != '$' && ft_strcmp(parse[1], "~"))
	{
		if (chdir(want_path) == -1)
			exit_code = hs_error_return(NULL, NULL, "failed to cd\n");
		cd_oldpwd(envp);
	}
	else if (!ft_strcmp(parse[1], "~"))
		cd_home(envp);
	free(want_path);
	free_parse(parse);
}
