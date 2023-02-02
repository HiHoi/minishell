/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hj_split_util4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:18:18 by hojsong           #+#    #+#             */
/*   Updated: 2023/02/02 20:13:55 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./test.h"

char	*hj_split_str_join(char **split)
{
	char	*result;
	char	*dest;
	int		i;

	i = 0;
	result = hj_ft_strdup("");
	while (split[i])
	{
		dest = result;
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

void	all_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}
