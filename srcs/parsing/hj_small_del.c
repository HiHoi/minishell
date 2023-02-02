/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hj_small_del.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:09:18 by hojsong           #+#    #+#             */
/*   Updated: 2023/02/02 20:17:28 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./test.h"

int	*hj_set_small_point(char *str)
{
	int	*result;
	int	count;
	int	i;
	int	ri;

	count = hj_small_count(str);
	result = malloc(sizeof(int) * count);
	i = 0;
	ri = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			result[ri++] = i;
			while (str[++i] != '\'')
				;
			result[ri++] = i;
		}
		else if (str[i] == '\"')
			while (str[++i] != '\"')
				;
		i++;
	}
	return (result);
}

int	hj_small_count(char *str)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			while (str[++i] != '\'')
				;
			result += 2;
		}
		else if (str[i] == '\"')
			while (str[++i] != '\"')
				;
		i++;
	}
	return (result);
}

char	*hj_del_small_save(char *str, int *set)
{
	char	*result;
	int		ri;
	int		i;
	int		si;

	result = malloc(sizeof(char) * (hj_ft_strlen(str) - hj_small_count(str) + 1));
	i = 0;
	si = 0;
	ri = 0;
	while (str[i])
	{
		if (i == set[si])
			si++;
		else
		{
			result[ri] = str[i];
			ri++;
		}
		i++;
	}
	result[ri] = '\0';
	return (result);
}
