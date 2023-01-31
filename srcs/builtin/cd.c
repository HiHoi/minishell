/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 20:36:20 by hosunglim         #+#    #+#             */
/*   Updated: 2023/01/31 18:52:31 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int  exit_code;

void	swap_env(char ***envp, char *src, char *key)
{
	int		i;
	char	*buf;

	i = -1;
	while ((*envp)[++i])
	{
		if (!ft_strncmp(key, (*envp)[i], ft_strlen(key)))
		{
			buf = (*envp)[i];
			(*envp)[i] = ft_strdup(src);
			free(buf);
			return ;
		}
	}
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
}

void	ft_cd(t_cmd *cmd, char ***envp)
{
	char	**parse;
	char	*pwd;
	char	*path;
	char	*want_path;

	parse = ft_split(cmd->str, ' ');
	pwd = parse_env_value("PWD", envp);
	path = ft_strjoin("/", parse[1]);
	want_path = ft_strjoin(pwd, path);
	if (ft_strcmp(parse[0], "cd"))
	{
		exit_code = 127;
		return ;
	}
	if (parse[1] != NULL && parse[1][0] != '$' && parse[1][0] != '~')
	{
		if (chdir(want_path) == -1)
			exit_code = hs_error_return(NULL, NULL, "failed to cd\n");
		cd_oldpwd(envp);
	}
	// else if (parse[1][0] == '~')
	// 	cd_home(cmd->str, envp);
	// else if (parse[1][0] == '$')
	// 	cd_envp(cmd->str, envp);
}
