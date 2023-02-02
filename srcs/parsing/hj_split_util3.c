/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hj_split_util3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:13:27 by hojsong           #+#    #+#             */
/*   Updated: 2023/02/02 20:34:26 by hoslim           ###   ########.fr       */
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
	split[i] = NULL;
	free(setpoint);
	return (split);
}

char	*hj_compare_split(char *str, int *idx, int *setpoint)
{
	char	*result;
	int		ri;
	int		i;

	if ((setpoint[*idx + 1] - setpoint[*idx] == 1) &&\
			setpoint[*idx] == '\"')
		*idx += 1;
	i = setpoint[*idx];
	if (str[i] == '\"')
		i++;
	result = malloc(sizeof(char) * (setpoint[*idx + 1] - i + 1));
	ri = 0;
	while (ri < setpoint[*idx + 1] - i)
	{
		result[ri] = str[i + ri];
		ri++;
	}
	result[ri] = '\0';
	return (result);
}
