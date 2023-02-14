/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hj_split_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 12:35:58 by hojsong           #+#    #+#             */
/*   Updated: 2023/02/14 14:00:25 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./test.h"

int	hj_set_count(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i += hj_compare_push(str, i, '\'');
			count++;
			count++;
		}
		if (str[i] == '\"')
		{
			i += hj_compare_push(str, i, '\"');
			count++;
			count++;
		}
		i++;
	}
	return (count);
}

int	*hj_set_seting(char *str, int count)
{
	int	i;
	int	*result;
	int	rdx;

	result = malloc(sizeof(int) * count);
	if (result == NULL)
		return (0);
	i = 0;
	rdx = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			result[rdx++] = i;
			if (str[i] == '\'')
				i += hj_compare_push(str, i, '\'');
			else
				i += hj_compare_push(str, i, '\"');
			result[rdx++] = i;
		}
		i++;
	}
	return (result);
}

char	*hj_str_save(char *str, int i, int j)
{
	char	*spr;
	int		idx;

	spr = malloc(sizeof(char) * (i - j + 2));
	if (spr == NULL)
		return (0);
	idx = 0;
	while (j + idx <= i)
	{
		spr[idx] = str[j + idx];
		idx++;
	}
	spr[idx] = '\0';
	return (spr);
}

int	hj_mal_size(char *str, char set)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			i += hj_compare_push(str, i, '\'');
		if (str[i] == '\"')
			i += hj_compare_push(str, i, '\"');
		if (str[i] != set && (str[i + 1] == set || str[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

int	hj_compare_push(char *str, int i, char set)
{
	int	i2;

	i2 = 1;
	while (str[i + i2])
	{
		if (str[i + i2] == set)
			return (i2);
		i2++;
	}
	hj_ft_error();
	return (0);
}
