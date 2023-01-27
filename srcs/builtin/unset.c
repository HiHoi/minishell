/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 20:38:13 by hosunglim         #+#    #+#             */
/*   Updated: 2023/01/27 13:25:21 by hoslim           ###   ########.fr       */
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

void	ft_unset(t_cmd *cmd, char **envp)
{
	int		i;
	int		len;
	char	**target;

	target = ft_split(cmd->str, ' ');
	if (target[1] == NULL)
		return ;
	i = -1;
	len = count_line(envp);
	while (++i < len)
	{
		if (check_key(envp[i], target[1]) == 1)
		{
			envp[i] = NULL;
			break ;
		}
	}
	return ;
}
