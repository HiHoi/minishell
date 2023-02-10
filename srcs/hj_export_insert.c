/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hj_export_insert.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:31:59 by hojsong           #+#    #+#             */
/*   Updated: 2023/02/09 20:49:48 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		hj_envp_last_size(char **str, char **envp);
int		hj_envp_check(char *str, char **envp);

char	**hj_export_insert(char **str, char **envp)
{
	char	**result;
	int		size;
	int		i;
	int		i2;

	size = hj_envp_last_size(str, envp);
	result = malloc(sizeof(char *) * (size + 1));
	if (result == NULL)
		return (0);
	i = 0;
	while (envp[i])
	{
		if (!hj_envp_check(envp[i], str))
			result[i] = envp[i];
		i++;
	}
	i2 = 0;
	while (str[i2])
	{
		result[i + i2] = str[i2];
		i2++;
	}
	result[i + i2] = NULL;
	return (result);
}

int	hj_envp_last_size(char **str, char **envp)
{
	int	i;
	int	size;

	size = 0;
	while (envp[size])
		size++;
	i = 0;
	while (str[i])
	{
		size += hj_envp_check(str[i], envp);
		i++;
	}
	return (size);
}

int	hj_envp_check(char *str, char **envp)
{
	int	i;
	int	idx;
	int	i2;

	idx = 0;
	while (str[idx] != '=')
		idx++;
	i = -1;
	while (envp[++i])
	{
		i2 = 0;
		while (envp[i][i2] == str[i2] && i2 < idx)
			i2++;
		if (envp[i][i2] == '=')
			return (0);
	}
	return (1);
}
