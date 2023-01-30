/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosunglim <hosunglim@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 20:36:20 by hosunglim         #+#    #+#             */
/*   Updated: 2023/01/29 21:49:00 by hosunglim        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int  exit_code;

void	cd_oldpwd(char ***envp)
{
	int		i;
	char	*cur;
	char	*old;
	// char	*pwd;
	char	*buf;

	i = -1;
	while ((*envp)[++i])
		if (check_key((*envp)[i], "PWD") > 0)
			break ;
	buf = getcwd(NULL, 1024);
	cur = ft_strjoin("PWD=", buf);
	old = ft_strdup((*envp)[i]);
	(void)old;
	(void)cur;
}

void	ft_cd(t_cmd *cmd, char ***envp)
{
	char    **parse;

	parse = ft_split(cmd->str, ' ');
	if (ft_strcmp(parse[0], "cd"))
	{
		exit_code = 127;
		return ;
	}
	if (parse[1] != NULL && parse[1][0] != '$' && parse[1][0] != '~')
	{
		if (chdir(parse[1]) == -1)
			exit_code = hs_error_return(NULL, NULL, "failed to cd\n");
		cd_oldpwd(envp);
	}
	// else if (parse[1][0] == '~')
	// 	cd_home(cmd->str, envp);
	// else if (parse[1][0] == '$')
	// 	cd_envp(cmd->str, envp);
}
