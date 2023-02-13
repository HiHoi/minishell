/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hj_split_change2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:14:13 by hojsong           #+#    #+#             */
/*   Updated: 2023/02/13 16:47:33 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./test.h"

char	*hj_envp_val(char *envp)
{
	char	*result;
	int		ri;
	int		i;

	ri = 0;
	i = 0;
	while (envp[i] != '=')
		i++;
	result = malloc(sizeof(char) * (hj_ft_strlen(envp) - i));
	while (envp[i + ri + 1])
	{
		result[ri] = envp[i + ri + 1];
		ri++;
	}
	result[ri] = '\0';
	return (result);
}

int	hj_is_envp(char *str, char *envp)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == envp[i])
			i++;
		else
			return (0);
	}
	if (envp[i] == '=')
		return (1);
	return (0);
}

int	hj_ft_isalpha(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

int	hj_ft_isen(char c)
{
	if (hj_ft_isalpha(c))
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	if (c == '_')
		return (1);
	return (0);
}
