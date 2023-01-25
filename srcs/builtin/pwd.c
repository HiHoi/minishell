/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosunglim <hosunglim@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 20:37:17 by hosunglim         #+#    #+#             */
/*   Updated: 2023/01/25 11:52:07 by hosunglim        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(t_cmd *cmd)
{
	char	*path;
	char	**test;

	test = ft_split(cmd->str, ' ');
	if (test[1])
		error(NULL, "Invalid option\n");
	path = getcwd(NULL, 1024);
	write(1, path, ft_strlen(path));
	write(1, "\n", 1);
	free(path);
	exit(0);
}
