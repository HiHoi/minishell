/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hj_split_util3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:13:27 by hojsong           #+#    #+#             */
/*   Updated: 2023/02/05 13:40:23 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./test.h"

char	**hj_save_split(char *str, int size)
{
	char	**split;
	int		*setpoint;
	int		i;
	int		i2;

	setpoint = hj_setpoint_seting(str);
	split = malloc(sizeof(char *) * (size + 1));
	if (split == NULL)
		return (0);
	i = 0;
	i2 = 0;
	while (i < size)
	{
		split[i] = hj_compare_split(str, &i2, setpoint);
		i++;
		i2++;
	}
	split[i] = 0;
	free(setpoint);
	return (split);
}

char	*hj_compare_split(char *str, int *idx, int *setpoint)
{
	char	*result;
	int		size;
	int		ri;
	int		i;
	int		chk;

	if ((setpoint[*idx + 1] - setpoint[*idx] == 1) && \
	str[setpoint[*idx]] != '$' && str[setpoint[*idx + 1]] != '\0')
		*idx += 1;
	i = setpoint[*idx];
	if (str[i] == '\0')
		return (0);
	chk = hj_point_checker(str, setpoint, *idx, str[i]);
	if (chk % 2 == 0 && str[i] != '$')
		i++;
	size = setpoint[*idx + 1];
	if (str[size] == '\'' && chk % 2 == 0)
		size++;
	result = malloc(sizeof(char) * (size - i + 1));
	ri = -1;
	while (++ri < size - i)
		result[ri] = str[i + ri];
	result[ri] = '\0';
	return (result);
}

int	hj_point_checker(char *str, int *set, int num, char com)
{
	int	result;
	int	i;
	int	idx;

	if (com == '$')
		return (1);
	i = 0;
	result = 0;
	while (i <= num)
	{
		idx = set[i];
		if (str[idx] == com)
			result++;
		i++;
	}
	return (result);
}
