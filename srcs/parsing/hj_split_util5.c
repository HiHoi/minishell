/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hj_split_util5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 19:38:07 by hojsong           #+#    #+#             */
/*   Updated: 2023/02/05 13:26:10 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./test.h"

int	*hj_setpoint_seting(char *str)
{
	int	*result;
	int	i;
	int	ri;

	result = malloc(sizeof(int) * (hj_set_mal_size(str) + 2));
	ri = 0;
	if (str[0] != '\"' && str[0] != '$' && str[0] != '\'')
		result[ri++] = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			result[ri++] = i;
			i += hj_set_compare_push(str, i);
			result[ri++] = i;
		}
		else if (str[i] == '\"')
		{
			result[ri++] = i++;
			while (str[i] != '\"')
			{
				if (str[i] == '$')
					result[ri++] = i;
				i++;
			}
			result[ri++] = i;
		}
		else if (str[i] == '$')
			result[ri++] = i;
		i++;
	}
	result[ri] = i;
	return (result);
}

int	hj_set_compare_push(char *str, int i)
{
	int	idx;

	idx = 1;
	while (str[i + idx] != '\'')
		idx++;
	return (idx);
}

int	hj_set_mal_size(char *str)
{
	int	i;
	int	result;

	i = 0;
	result = 1;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			while (str[++i] != '\'')
				;
			result += 2;
		}
		else if (str[i] == '\"')
			result += hj_compare_push2(str, &i);
		else if (str[i] == '$')
			result++;
		i++;
	}
	return (result);
}

int	hj_compare_push2(char *str, int *i)
{
	int	result;

	result = 0;
	*i += 1;
	while (str[*i] != '\"')
	{
		if (str[*i] == '$')
			result++;
		*i += 1;
	}
	return (result + 2);
}
