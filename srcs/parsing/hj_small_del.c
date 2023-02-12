/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hj_small_del.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hojsong <hojsong@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:09:18 by hojsong           #+#    #+#             */
/*   Updated: 2023/02/12 17:58:24 by hojsong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./test.h"

char	**hj_del_small(char **str, int size)
{
	char	**result;
	int		i;

	i = 0;
	result = malloc(sizeof(char *) * (size + 1));
	result[size] = 0;
	i = 0;
	while (i < size)
	{
		if (str[i] && str[i + 1])
			result[i] = hj_last_rt_string(str[i], str[i + 1]);
		else if (str[i] && str[i + 1] == NULL)
			result[i] = hj_last_rt_string(str[i], "");
		else
			result[i] = hj_ft_strdup("");
		i++;
	}
	return (result);
}

char	*hj_last_rt_string(char *str, char *str2)
{
	char	*result;
	int		rsize;
	int		add;
	int		i;

	if (str[0] == '$' && str[1] == '\0' && str2 && \
				(str2[0] == '\'' || str2[0] == '\"'))
		return (hj_ft_strdup(""));
	if (str[0] == '\'' || str[0] == '\"')
		add = 1;
	else
		add = 0;
	rsize = hj_ft_strlen(str) - add;
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
