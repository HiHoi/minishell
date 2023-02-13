/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:47:28 by hoslim            #+#    #+#             */
/*   Updated: 2023/02/13 15:14:08 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_code;

int	count_line(char **line)
{
	int	i;

	if (line == NULL)
		return (0);
	i = 0;
	while (line[i])
		i++;
	return (i);
}

void	free_info(t_info *info)
{
	clear_history();
	if (info->cmd)
		free(info->cmd);
	if (info)
		free(info);
}

int	error(t_info *info, char *s, int flag)
{
	if (info)
		free_info(info);
	if (s)
	{
		write(2, "minishell: ", 11);
		write(2, s, ft_strlen(s));
		if (flag == 1)
		{
			write(2, ": No such file or directory\n", 29);
			g_exit_code = 1;
		}
		if (flag == 2)
		{
			write(2, ": command not found\n", 21);
			g_exit_code = 127;
		}
	}
	exit(g_exit_code);
}

int	hs_error_return(t_info *info, t_cmd *cmd, char *s)
{
	if (info)
		free_info(info);
	if (cmd)
		free(cmd);
	if (s)
		write(2, s, ft_strlen(s));
	g_exit_code = 127;
	return (g_exit_code);
}
