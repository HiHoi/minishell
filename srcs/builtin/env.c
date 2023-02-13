/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 20:38:32 by hosunglim         #+#    #+#             */
/*   Updated: 2023/02/13 14:40:41 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_code;

void	env_option(char *str, char ***envp)
{
	char	**test;

	test = hj_split_cmd(str, *envp);
	if (test[1] != NULL && ft_strchr(str, '$') == 0)
	{
		printf("env: %s: No such file or dir\n", test[1]);
		g_exit_code = 127;
		exit(g_exit_code);
	}
	if (test[1] != NULL && test[1][0] != '\0')
	{
		printf("minishell: %s\n", test[1]);
		g_exit_code = 127;
		exit(g_exit_code);
	}
}

void	ft_env(t_cmd *cmd, char ***envp)
{
	int		i;

	cmd->exec_flag = 1;
	if (*envp == NULL)
		return ;
	env_option(cmd->str, envp);
	i = 0;
	while ((*envp)[i])
	{
		if ((*envp)[i][0] != '\0' && ft_strchr((*envp)[i], '='))
		{
			write(1, (*envp)[i], ft_strlen((*envp)[i]));
			write(1, "\n", 1);
		}
		i++;
	}
	g_exit_code = 0;
}
