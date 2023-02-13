/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hj_envp_bigtaging.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:57:56 by hojsong           #+#    #+#             */
/*   Updated: 2023/02/13 20:05:15 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	hj_envp_name_chk(char *str)
{
	int	i;

	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (1);
	i = 1;
	while (str[i])
	{
		if (ft_isalpha(str[i]) || ft_isdigit(str[i]) || \
			str[i] == '_')
			i++;
		else
			break ;
	}
	if (str[i] != '=' && str[i])
		return (1);
	return (0);
}

void	hj_resultinit(char **result, char *str)
{
	int	i;
	int	i2;

	i = 0;
	while (str[i] != '=' && str[i])
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
	i = 0;
	i2 = 0;
	while (str[i] != '=' && str[i])
		result[0][i2++] = str[i++];
	result[0][i2] = '\0';
	i2 = 0;
	if (str[i] != '\0')
	{
		while (str[++i])
			result[1][i2++] = str[i];
	}
	result[1][i2] = '\0';
	result[2] = NULL;
	return (result);
}
