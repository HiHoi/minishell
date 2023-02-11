/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hj_redirection_split.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 20:25:39 by hojsong           #+#    #+#             */
/*   Updated: 2023/02/11 15:02:05 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		hj_is_redc(char c);
char	*hj_redc_string(char *str, int *idx);
char	*hj_save_redc_str(char *str, int *idx, int i);
int		hj_redc_size(char *str);

char	**hj_redc_spilit(char *str)
{
	char	**result;
	int		size;
	int		i;
	int		idx;

	size = hj_redc_size(str);
	result = malloc(sizeof(char *) * (size + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	idx = 0;
	while (i < size)
	{
		result[i] = hj_redc_string(str, &idx);
		i++;
	}
	result[i] = 0;
	return (result);
}

int	hj_is_redc(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

char	*hj_redc_string(char *str, int *idx)
{
	char	*result;
	int		i;
	int		count;

	count = 0;
	i = 0;
	if (str[*idx + i] == '\0')
		return (NULL);
	while (str[*idx + i])
	{
		if (hj_is_redc(str[*idx + i]) && count == 0)
		{
			if (hj_is_redc(str[*idx + i + 1]))
				i++;
			count++;
		}
		else if (hj_is_redc(str[*idx + i]) && count == 1)
			break ;
		i++;
	}
	result = hj_save_redc_str(str, idx, i - 1);
	*idx += i;
	return (result);
}

char	*hj_save_redc_str(char *str, int *idx, int i)
{
	char	*result;
	int		j;

	j = 0;
	result = malloc(sizeof(char) * (i + 2));
	if (result == NULL)
		return (0);
	while (j <= i)
	{
		result[j] = str[*idx + j];
		j++;
	}
	result[j] = '\0';
	return (result);
}

int	hj_redc_size(char *str)
{
	int	result;
	int	i;

	result = 1;
	i = 0;
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<')
		{
			if (str[i + 1] == '>' || str[i + 1] == '<')
				i++;
			result++;
		}
		i++;
	}
	return (result);
}
