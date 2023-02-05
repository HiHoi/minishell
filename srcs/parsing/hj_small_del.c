/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hj_small_del.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:09:18 by hojsong           #+#    #+#             */
/*   Updated: 2023/02/05 13:38:52 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./test.h"

char	**hj_del_small(char **str)
{
	char	**result;
	int		i;

	i = 0;
	while (str[i])
		i++;
	result = malloc(sizeof(char *) * (i + 1));
	result[i] = NULL;
	i = 0;
	while (str[i])
	{
		result[i] = hj_last_rt_string(str[i]);
		i++;
	}
	return (result);
}

char	*hj_last_rt_string(char *str)
{
	char	*result;
	int		rsize;
	int		add;
	int		i;

	add = 1;
	if (str[0] == '\'')
		rsize = hj_ft_strlen(str) - 1;
	else if (str[0] == '\"')
		rsize = hj_ft_strlen(str) - 1;
	else
	{
		add = 0;
		rsize = hj_ft_strlen(str);
	}
	result = malloc(sizeof(char) * (rsize + 1));
	i = 0;
	while (i < rsize)
	{
		result[i] = str[i + add];
		i++;
	}
	result[i] = '\0';
	return (result);
}
