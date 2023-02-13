/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:13:49 by hoslim            #+#    #+#             */
/*   Updated: 2023/02/13 16:51:00 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*set_shlvl(char *str)
{
	int		level;
	char	*parse;
	char	*ret;
	char	*level_c;

	parse = ft_substr(str, 6, ft_strlen(str) - 6);
	level = ft_atoi(parse);
	level_c = ft_itoa(level + 1);
	ret = ft_strjoin("SHLVL=", level_c);
	free(parse);
	free(level_c);
	return (ret);
}

t_info	*init_info(char **envp)
{
	t_info	*info;
	char	*temp;
	int		i;
	int		len;

	len = count_line(envp);
	info = malloc(sizeof(t_info) * 1);
	info->cmd = NULL;
	info->en = malloc(sizeof(char *) * (len + 1));
	i = -1;
	while (++i < len)
	{
		if (!ft_strncmp(envp[i], "SHLVL", 5))
		{
			temp = set_shlvl(envp[i]);
			info->en[i] = ft_strdup(temp);
			free(temp);
		}
		else
			info->en[i] = ft_strdup(envp[i]);
	}
	info->en[len] = NULL;
	return (info);
}

t_cmd	*init_cmd(void)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd) * 1);
	new->exec_flag = 0;
	new->parent_flag = 0;
	new->parse_flag = 0;
	new->type = 0;
	new->str = NULL;
	new->left = NULL;
	new->right = NULL;
	return (new);
}
