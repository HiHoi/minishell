/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hj_split_util2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:33:12 by hojsong           #+#    #+#             */
/*   Updated: 2023/02/02 20:31:37 by hoslim           ###   ########.fr       */
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
			hj_pashing_push(str, &i, '\'');
		else if (str[i] == '\"')
			result += hj_pashing_push(str, &i, '\"');
		if (str[i] != '$' && (str[i + 1] == '$' || str[i + 1] == '\0'))
			result++;
		else if (str[i] == '$' && str[i + 1] == '\0')
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
	result = 1;
	if (str[*i + idx] == set)
	{
		*i += idx;
		return (0);
	}
	while (str[*i + idx] != set)
	{
		if (str[*i + idx] != '$' && str[*i + idx + 1] == '$' && set != '\'')
			result++;
		idx++;
	}
	*i += idx;
	return (result);
}

int	hj_check_small(char *str)
{
	int	i;
	int	result;

	result = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			while (str[++i] != '\'')
				result = 1;
		}
		else if (str[i] == '\"')
		{
			while (str[++i] != '\"')
				;
		}
		i++;
	}
	return (result);
}

char	*hj_del_small(char *str)
{
	char	*result;
	int		*set;
	int		ri;
	int		i;

	i = 0;
	ri = 0;
	set = hj_set_small_point(str);
	result = hj_del_small_save(str, set);
	free(set);
	free(str);
	return (result);
}
