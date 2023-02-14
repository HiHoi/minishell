/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 20:38:13 by hosunglim         #+#    #+#             */
/*   Updated: 2023/02/14 13:26:28 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//전부 unset하고 unset하면 어떻게 될까?

int	check_key(char *envp, char *src)
{
	int	i;

	i = 0;
	while (envp[i] != '=')
	{
		if (envp[i] == src[i])
			i++;
		else
			return (0);
	}
	if (src[i] == '\0')
		return (1);
	return (0);
}

//여러 개의 밸류가 들어오면 그것도 처리

void	ft_unset(t_cmd *cmd, char ***envp)
{
	int		idx;
	char	**target;
	char	**ret;

	cmd->exec_flag = 1;
	if (*envp == NULL)
		return ;
	target = hj_split_cmd(cmd->str, *envp);
	if (target[1] == NULL || hs_check_envp(envp, target[1]) == 0)
	{
		free_parse(target);
		return ;
	}
	idx = 0;
	while (target[++idx])
	{
		if (target[idx][0] != '\0')
		{
			ret = hj_envp_del(*envp, target[idx]);
			*envp = ret;
		}
	}
	free_parse(target);
}
