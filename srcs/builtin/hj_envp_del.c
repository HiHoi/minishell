/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hj_envp_del.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:41:22 by hojsong           #+#    #+#             */
/*   Updated: 2023/02/06 14:34:43 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	hj_envp_free_all(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

char	*hj_save_str_envp(char *str)
{
	char	*result;
	int		i;

	i = 0;
	while (str[i])
		i++;
	result = malloc(sizeof(char) * (i + 1));
	if (result == NULL)
		return (0);
	i = 0;
	while (str[i])
	{
		result[i] = str[i];
		i++;
	}
	result[i] = 0;
	return (result);
}

int	hj_is_del_envp(char *envp, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (envp[i] == str[i])
			i++;
		else
			return (0);
	}
	if (envp[i] == '=')
		return (1);
	return (0);
}

char	**hj_envp_size(char **envp)
{
	char	**result;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	result = malloc(sizeof(char *) * i);
	if (result == NULL)
		return (0);
	result[i - 1] = NULL;
	return (result);
}

char	**hj_envp_del(char **envp, char *str)
{
	char	**result;
	int		i;
	int		i2;

	result = hj_envp_size(envp);
	i = 0;
	i2 = 0;
	while (envp[i])
	{
		if (hj_is_del_envp(envp[i], str) == 0)
			result[i2++] = ft_strdup(envp[i]);
		i++;
	}
	result[i2] = NULL;
	hj_envp_free_all(envp);
	return (result);
}
