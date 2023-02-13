/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hj_export_insert.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:31:59 by hojsong           #+#    #+#             */
/*   Updated: 2023/02/13 19:44:09 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		hj_envp_last_size(char **str, char **envp);
int		hj_envp_check(char *str, char **envp);
int		hj_chk_str(char *str, char **envp);
int		hj_chk_env(char **str, char *envp);

char	**hj_export_insert(char **str, char **envp)
{
	char	**result;
	int		i;
	int		i2;

	result = malloc(sizeof(char *) * (hj_envp_last_size(str, envp) + 1));
	if (result == NULL)
		return (0);
	i = 0;
	i2 = 0;
	while (envp[i])
	{
		if (hj_chk_env(str, envp[i]))
			result[i - i2] = ft_strdup(envp[i]);
		else
			i2++;
		i++;
	}
	i -= i2;
	i2 = 0;
	while (str[++i2])
		if (hj_chk_str(str[i2], envp))
			result[i++] = ft_strdup(str[i2]);
	result[i] = 0;
	return (result);
}

int	hj_chk_env(char **str, char *envp)
{
	int	idx;
	int	i2;
	int	i;

	idx = 0;
	while (envp[idx] != '=' && envp[idx])
		idx++;
	i = 0;
	while (str[++i])
	{
		i2 = 0;
		while (i2 < idx && str[i][i2] && str[i][i2] == envp[i2])
			i2++;
		if (i2 == idx && str[i][i2] == '=')
			return (0);
		if (i2 == idx && str[i][i2] == '\0')
			return (1);
	}
	return (1);
}

int	hj_chk_str(char *str, char **envp)
{
	int	idx;
	int	i2;
	int	i;

	idx = 0;
	while (str[idx] && str[idx] != '=')
		idx++;
	i = -1;
	while (envp[++i])
	{
		i2 = 0;
		while (i2 < idx && envp[i][i2] && str[i2] == envp[i][i2])
			i2++;
		if (i2 == idx && str[i2] == '\0')
			return (0);
		if (i2 == idx && (envp[i][i2] == '\0' || envp[i][i2] == '='))
			return (1);
	}
	return (1);
}

int	hj_envp_last_size(char **str, char **envp)
{
	int	i;
	int	size;

	size = 0;
	while (envp[size])
		size++;
	i = 1;
	while (str[i])
	{
		if (hj_envp_check(str[i], envp))
			size++;
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
	while (str[idx] && str[idx] != '=')
		idx++;
	i = -1;
	while (envp[++i])
	{
		i2 = 0;
		while (i2 < idx && envp[i][i2] && str[i2] == envp[i][i2])
			i2++;
		if (i2 == idx && (envp[i][i2] == '=' || envp[i][i2] == '\0'))
			return (0);
	}
	return (1);
}
