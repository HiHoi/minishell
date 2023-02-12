/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hj_split_util3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hojsong <hojsong@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:13:27 by hojsong           #+#    #+#             */
/*   Updated: 2023/02/12 17:53:51 by hojsong          ###   ########.fr       */
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
	while (i < size && setpoint[i2] < hj_ft_strlen(str))
	{
		split[i] = hj_compare_split(str, &i2, setpoint);
		i++;
		i2++;
	}
	while (i < size)
		split[i++] = hj_ft_strdup("");
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

	hj_is_set(str, idx, setpoint);
	i = setpoint[*idx];
	if (i >= hj_ft_strlen(str) || setpoint[*idx + 1] > hj_ft_strlen(str))
		return (0);
	chk = hj_point_checker(str, setpoint, idx, str[i]);
	if (chk % 2 == 0 && str[i] != '$')
		i++;
	size = setpoint[*idx + 1];
	if (str[size] == '\'' && chk % 2 == 0)
		size++;
	result = malloc(sizeof(char) * (size - i + 1));
	if (result == NULL)
		return (0);
	ri = -1;
	while (++ri < size - i)
		result[ri] = str[i + ri];
	result[ri] = '\0';
	return (result);
}

void	hj_is_set(char *str, int *idx, int *setpoint)
{
	if ((setpoint[*idx + 1] - setpoint[*idx] == 1) && \
			(str[setpoint[*idx]] == '\"' || \
			str[setpoint[*idx]] == '\'') && \
			str[setpoint[*idx + 1]] != '\0')
		*idx += 1;
}

char	**hj_set_int(char *str, int *i)
{
	char	**spr;
	int		size;

	if (str == NULL)
		return (0);
	size = hj_mal_size(str, ' ');
	spr = malloc(sizeof(char *) * (size + 1));
	if (spr == NULL)
		return (0);
	spr[size] = NULL;
	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	return (spr);
}

int	hj_point_checker(char *str, int *set, int *num, char com)
{
	int		result;
	int		i;
	int		idx;

	if (com != '\'' && com != '\"')
		return (1);
	else if (*num >= hj_ft_strlen(str))
		return (0);
	i = 0;
	result = 0;
	while (i <= *num)
	{
		idx = set[i];
		if (str[idx] == com)
			result++;
		i++;
	}
	return (result);
}
