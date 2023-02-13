/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hj_split_change.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 15:41:24 by hojsong           #+#    #+#             */
/*   Updated: 2023/02/13 16:47:08 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./test.h"

extern int	g_exit_code;

char	**hj_change_split(char **str, char **envp)
{
	char	**result;
	int		i;

	i = 0;
	while (str[i])
		i++;
	result = malloc(sizeof(char *) * (i + 1));
	if (result == NULL)
		return (0);
	i = 0;
	while (str[i])
	{
		result[i] = hj_envp_change(str[i], envp);
		i++;
	}
	result[i] = 0;
	free(str);
	return (result);
}

char	*hj_envp_change(char *str, char **envp)
{
	char	*result;
	char	*set;
	int		i;

	if (str[0] != '$')
		return (str);
	else if (str[1] == '?')
	{
		i = 2;
		free(str);
		return (hj_ft_atoi(g_exit_code));
	}
	else if ((!hj_ft_isalpha(str[1]) || str[1] == '\0'))
		return (str);
	set = hj_find_envp_val(str, &i, envp);
	if (i == hj_ft_strlen(str))
	{
		free(str);
		return (set);
	}
	result = hj_envp_plus_str(set, str, i);
	free(str);
	free(set);
	return (result);
}

char	*hj_find_envp_val(char *str, int *i, char **envp)
{
	char	*result;
	char	*find;
	int		idx;

	idx = 0;
	find = hj_envp_name(str);
	*i = (hj_ft_strlen(find) + 1);
	while (envp[idx])
	{
		if (hj_is_envp(find, envp[idx]))
		{
			result = hj_envp_val(envp[idx]);
			free(find);
			return (result);
		}
		idx++;
	}
	free(find);
	return (0);
}

char	*hj_envp_name(char *str)
{
	char	*result;
	int		i;

	i = 1;
	while (hj_ft_isen(str[i]) && str[i])
		i++;
	result = malloc(sizeof(char) * i);
	i = 0;
	while (hj_ft_isen(str[i + 1]))
	{
		result[i] = str[i + 1];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*hj_envp_plus_str(char *set, char *str, int i)
{
	char	*result;
	int		idx;
	int		size;
	int		set_size;

	set_size = hj_ft_strlen(set);
	size = set_size + hj_ft_strlen(str) - i;
	result = malloc(sizeof(char) * (size + 1));
	if (result == NULL)
		return (0);
	idx = 0;
	while (idx < size)
	{
		if (idx < set_size)
			result[idx] = set[idx];
		else
			result[idx] = str[i + idx - set_size];
		idx++;
	}
	result[idx] = '\0';
	return (result);
}
