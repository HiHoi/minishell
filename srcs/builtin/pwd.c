/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 20:37:17 by hosunglim         #+#    #+#             */
/*   Updated: 2023/02/06 11:55:21 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(t_cmd *cmd)
{
	char	*path;
	char	**test;

	cmd->exec_flag = 1;
	test = ft_split(cmd->str, ' ');
	if (test[1])
		error(NULL, "Invalid option\n", -1);
	path = getcwd(NULL, 1024);
	write(1, path, ft_strlen(path));
	write(1, "\n", 1);
	free(path);
	exit(0);
}
