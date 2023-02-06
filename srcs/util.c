/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:47:28 by hoslim            #+#    #+#             */
/*   Updated: 2023/02/06 13:10:28 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exit_code;

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
			exit_code = 1;
		}
		if (flag == 2)
		{
			write(2, ": command not found\n", 21);
			exit_code = 127;
		}
	}
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
	int		len;

	len = count_line(envp);
	info = malloc(sizeof(t_info) * 1);
	info->cmd = NULL;
	info->en = malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (i < len)
	{
		info->en[i] = ft_strdup(envp[i]);
		i++;
	}
	info->en[len] = NULL;
	return (info);
}
