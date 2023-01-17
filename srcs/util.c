/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:47:28 by hoslim            #+#    #+#             */
/*   Updated: 2023/01/17 12:58:49 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exit_code;

int	count_line(char **line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	return (i);
}

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
	exit(exit_code);
}

int	hs_error_return(t_info *info, t_cmd *cmd, char *s)
{
	if (info)
		free_info(info);
	if (cmd)
		free(cmd);
	if (s)
		write(2, s, ft_strlen(s));
	exit_code = 127;
	return (exit_code);
}

t_info	*init_info(char **envp)
{
	t_info	*info;
	int		i;

	info = ft_calloc(1, sizeof(t_info));
	info->cmd = ft_calloc(1, sizeof(t_cmd));
	info->en = ft_calloc(count_line(envp), sizeof(char *));
	i = -1;
	while (envp[++i])
		info->en[i] = ft_strdup(envp[i]);
	info->en[i] = NULL;
	return (info);
}
