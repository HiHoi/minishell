/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosunglim <hosunglim@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 20:38:32 by hosunglim         #+#    #+#             */
/*   Updated: 2023/01/25 11:23:33 by hosunglim        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    ft_env(t_cmd *cmd, char **envp)
{
    int     i;
    char    **test;

    test = ft_split(cmd->str, ' ');
    if (test[1])
        error(NULL, "Invaild option\n");
    i = 0;
    while (envp[i])
    {
        write(1, envp[i], ft_strlen(envp[i]));
        write(1, "\n", 1);
        i++;
    }
    exit(0);
}
