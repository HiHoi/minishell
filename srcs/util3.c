/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 12:46:02 by hoslim            #+#    #+#             */
/*   Updated: 2023/02/06 12:46:21 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*hs_parsing_cmd(char ***envp, char *cmdline)
{
	char	*parsed;
	char	**path;

	path = pipe_parsing_envp(envp);
	parsed = pipe_parsing_cmd(path, cmdline);
	free_parse(path);
	return (parsed);
}

int	check_argc(char *str)
{
	int		ret;

	if (str && ft_isalpha(str[0]) == 1)
		ret = 0;
	else
		ret = 2;
	return (ret);
}
