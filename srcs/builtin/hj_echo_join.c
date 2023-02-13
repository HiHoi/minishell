/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hj_echo_join.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 16:01:39 by hojsong           #+#    #+#             */
/*   Updated: 2023/02/13 19:09:06 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*hj_str_echo_join(char *str1, char *str2)
{
	char	*result;
	int		i;
	int		s1_size;

	if (str1 == NULL || str2 == NULL)
		return (0);
	s1_size = (int)ft_strlen(str1);
	result = malloc(sizeof(char) * (s1_size + (int)ft_strlen(str2) + 2));
	if (result == NULL)
		return (0);
	i = -1;
	while (str1[++i])
		result[i] = str1[i];
	result[i] = ' ';
	while (str2[++i - s1_size - 1])
		result[i] = str2[i - s1_size - 1];
	result[i] = '\0';
	return (result);
}

char	*hj_echo_join(char **str, int i)
{
	char	*result;
	char	*dest;
	int		idx;

	idx = 1;
	if (str[i] == NULL)
		return (NULL);
	result = ft_strdup(str[i]);
	while (str[i + idx])
	{
		dest = result;
		result = hj_str_echo_join(dest, str[i + idx]);
		free(dest);
		dest = NULL;
		idx++;
	}
	return (result);
}

int	check_option(char **str, int *option)
{
	int	i;
	int	j;

	i = 0;
	while (str[++i])
	{
		if (str[i][0] != '-')
			break ;
		j = 0;
		while (str[i][++j])
		{
			if (str[i][j] != 'n')
				break ;
		}
		if (str[i][j])
			break ;
	}
	if (i > 1)
		*option = 1;
	return (i);
}
