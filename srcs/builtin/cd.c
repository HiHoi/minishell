/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 20:36:20 by hosunglim         #+#    #+#             */
/*   Updated: 2023/02/06 18:30:51 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_code;

char	*cd_parse_path(char *cmd, char ***envp)
{
	char	*want;
	char	*pwd;
	char	*path;
	char	**parse;

	if (envp == NULL || hs_check_envp(envp, "PWD=") == 0)
		return (0);
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

	if (envp == NULL || hs_check_envp(envp, "PWD=") == 0 \
	|| hs_check_envp(envp, "OLDPWD="))
		return ;
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

	if (envp == NULL || hs_check_envp(envp, "HOME=") == 0)
	{
		write(2, "minishell: cd: HOME not set\n", 29);
		g_exit_code = 1;
		return ;
	}
	path = parse_env_value("HOME", envp);
	if (chdir(path) == -1)
	{
		free(path);
		g_exit_code = 127;
		return ;
	}
	free(path);
}

void	ft_cd(t_cmd *cmd, char ***envp)
{
	char	**parse;
	char	*want_path;

	cmd->exec_flag = 1;
	parse = ft_split(cmd->str, ' ');
	if (!ft_strcmp(cmd->str, "cd"))
	{
		free_parse(parse);
		g_exit_code = 127;
		return ;
	}
	want_path = cd_parse_path(cmd->str, envp);
	if (parse[1] != NULL && parse[1][0] != '$' && ft_strcmp(parse[1], "~"))
	{
		if (chdir(want_path) == -1)
			g_exit_code = hs_error_return(NULL, NULL, "failed to cd\n");
		cd_oldpwd(envp);
	}
	else if (!ft_strcmp(parse[1], "~"))
		cd_home(envp);
	free(want_path);
	free_parse(parse);
}
