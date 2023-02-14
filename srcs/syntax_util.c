/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:16:07 by hoslim            #+#    #+#             */
/*   Updated: 2023/02/14 16:50:17 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	hj_compare_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			while (str[++i] && str[i] != '\'')
				;
		else if (str[i] == '\"')
			while (str[++i] && str[i] != '\"')
				;
		if (str[i] == '\0')
			return (0);
		if (str[i] == ';' || str[i] == '\\' || str[i] == '*')
			return (0);
		i++;
	}
	return (1);
}
