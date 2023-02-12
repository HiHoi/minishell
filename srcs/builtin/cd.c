/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 20:36:20 by hosunglim         #+#    #+#             */
/*   Updated: 2023/02/12 19:38:47 by hoslim           ###   ########.fr       */
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

	if (envp == NULL || hs_check_envp(envp, "PWD=") == 0 || cmd == NULL)
		return (NULL);
	parse = hj_split_cmd(cmd, *envp);
	path = ft_strjoin("/", parse[1]);
	pwd = parse_env_value("PWD", envp);
	if (parse[1][0] != '/')
		want = ft_strjoin(pwd, path);
	else
		want = ft_strjoin("", path);
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
	|| hs_check_envp(envp, "OLDPWD=") == 0)
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
	cd_oldpwd(envp);
	g_exit_code = 0;
}

void	cd_error(char *str)
{
	write(2, "minishell: cd: ", 16);
	write(2, str, ft_strlen(str));
	write(2, ": No such file or direc\n", 25);
	g_exit_code = 1;
}

void	ft_cd(t_cmd *cmd, char ***envp)
{
	char	**parse;

	cmd->exec_flag = 1;
	parse = hj_split_cmd(cmd->str, *envp);
	if (parse[1] == NULL || !ft_strcmp(parse[1], "~"))
	{
		cd_home(envp);
		free_parse(parse);
		return ;
	}
	if (parse[1] != NULL && parse[1][0] != '$' && ft_strcmp(parse[1], "~"))
	{
		if (chdir(parse[1]) == -1)
			cd_error(parse[1]);
		cd_oldpwd(envp);
	}
	free_parse(parse);
	g_exit_code = 0;
}
