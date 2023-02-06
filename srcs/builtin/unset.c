/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 20:38:13 by hosunglim         #+#    #+#             */
/*   Updated: 2023/02/06 14:27:44 by hoslim           ###   ########.fr       */
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
	if (envp[i] == '=')
		return (1);
	return (0);
}

//여러 개의 밸류가 들어오면 그것도 처리

void	ft_unset(t_cmd *cmd, char ***envp)
{
	char	**target;
	char	**ret;

	cmd->exec_flag = 1;
	if (*envp == NULL)
		return ;
	target = ft_split(cmd->str, ' ');
	if (target[1] == NULL)
	{
		free_parse(target);
		return ;
	}
	ret = hj_envp_del(*envp, target[1]);
	*envp = ret;
	free_parse(target);
}
