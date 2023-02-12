/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hj_split_util4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hojsong <hojsong@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:18:18 by hojsong           #+#    #+#             */
/*   Updated: 2023/02/12 20:17:14 by hojsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./test.h"

char	*hj_split_str_join(char **split, int size)
{
	char	*result;
	char	*dest;
	int		i;

	i = 0;
	result = hj_ft_strdup("");
	while (i < size)
	{
		dest = result;
		if (split[i] == NULL)
			result = hj_ft_strjoin(dest, hj_ft_strdup(""));
		else
			result = hj_ft_strjoin(dest, split[i]);
		free(dest);
		dest = NULL;
		i++;
	}
	return (result);
}

char	*hj_ft_strjoin(char *str, char *str2)
{
	char	*result;
	int		i;
	int		size;
	int		strlen;

	strlen = hj_ft_strlen(str);
	size = strlen + hj_ft_strlen(str2);
	result = malloc(sizeof(char) * (size + 1));
	if (result == NULL)
		return (0);
	i = -1;
	while (++i < strlen)
		result[i] = str[i];
	while (i < size)
	{
		result[i] = str2[i - strlen];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*hj_ft_strdup(char *str)
{
	char	*result;
	int		i;

	result = malloc(sizeof(char) * (hj_ft_strlen(str) + 1));
	i = 0;
	while (str[i])
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

void	all_free(char **str, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}
