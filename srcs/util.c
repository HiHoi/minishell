/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:47:28 by hoslim            #+#    #+#             */
/*   Updated: 2023/01/15 19:57:04 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_info(t_info *info)
{
	if (info->cmd)
		free(info->cmd);
	if (info)
		free(info);
}

int	error(t_info *info, char *s)
{
	if (info)
		free_info(info);
	if (s)
		write(2, s, ft_strlen(s));
	return (ERROR);
}

t_info	*init_info(void)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	info->cmd = malloc(sizeof(t_cmd));
	if (!info->cmd)
		return (NULL);
	return (info);
}
