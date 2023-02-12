/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hj_envp_bigtaging.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:57:56 by hojsong           #+#    #+#             */
/*   Updated: 2023/02/06 14:52:50 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	hj_resultinit(char **result, char *str)
{
	int	i;
	int	i2;

	i = 0;
	while (str[i] != '=')
		i++;
	i2 = 0;
	while (str[i + i2])
		i2++;
	result[0] = malloc(sizeof(char) * (i + 1));
	if (result[0] == NULL)
		return ;
	result[1] = malloc(sizeof(char) * (i2 + 1));
	if (result[1] == NULL)
		return ;
}

char	**hj_envp_bigtaging(char *str)
{
	char	**result;
	int		i;
	int		i2;

	result = malloc(sizeof(char *) * 3);
	if (result == NULL)
		return (0);
	hj_resultinit(result, str);
	i = -1;
	i2 = 0;
	while (str[++i] != '=')
		result[0][i2++] = str[i];
	result[0][i2] = '\0';
	i2 = 0;
	while (str[++i])
		result[1][i2++] = str[i];
	result[1][i2] = '\0';
	result[2] = NULL;
	return (result);
}
