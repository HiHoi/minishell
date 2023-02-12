/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hj_split_util2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hojsong <hojsong@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:33:12 by hojsong           #+#    #+#             */
/*   Updated: 2023/02/12 17:54:09 by hojsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./test.h"

int	hj_sp_mal_size(char *str)
{
	int	result;
	int	i;

	i = 0;
	result = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			result += hj_pashing_push(str, &i, '\'');
		else if (str[i] == '\"')
			result += hj_pashing_push(str, &i, '\"');
		if ((str[i] == '\'' || str[i] == '\"') && \
				str[i + 1] != '\0')
			result++;
		if (str[i + 1] == '$')
			result++;
		else if (str[i] == '$' && str[i + 1] == '$')
			result++;
		if (str[i] != '\'' && str[i] != '\"' && str[i + 1] == '\0')
			result++;
		i++;
	}
	return (result);
}

int	hj_pashing_push(char *str, int *i, char set)
{
	int	result;
	int	idx;

	idx = 1;
	result = 2;
	if (str[*i + 1] == set)
	{
		*i += idx;
		return (result);
	}
	while (str[*i + idx] != set)
	{
		if (str[*i + idx] == '$' && set != '\'')
			result++;
		idx++;
	}
	if (str[*i + idx + 1] != '\0')
		result++;
	*i += idx;
	return (result);
}

char	*hj_ft_atoi(int num)
{
	char	*result;
	int		size;
	int		i;

	size = hj_set_atoi_size(num);
	result = malloc(sizeof(char) * size + 1);
	if (result == NULL)
		return (0);
	result[size] = '\0';
	i = 0;
	if (num < 0)
	{
		num *= -1;
		i = 1;
	}
	while (--size - i >= 0)
	{
		result[size] = (num % 10) + '0';
		num /= 10;
	}
	if (i == 1)
		result[0] = '-';
	return (result);
}

int	hj_set_atoi_size(int num)
{
	int	result;
	int	renum;

	result = 0;
	renum = num;
	if (renum <= 0)
		result++;
	while (renum != 0)
	{
		renum /= 10;
		result++;
	}
	return (result);
}
