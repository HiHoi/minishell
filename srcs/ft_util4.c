/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 12:42:27 by hoslim            #+#    #+#             */
/*   Updated: 2023/02/14 13:14:28 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_exit_code;

int	nbrcheck(const char *str)
{
	int	result;
	int	i;

	result = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' \
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
	{
		result = -1;
		i++;
	}
	return (result);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	result;
	int	ne;

	if (str == NULL)
		return (0);
	i = 0;
	result = 0;
	ne = nbrcheck(str);
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			result = result * 10 + ((str[i] - 48) * ne);
		else
			return (result);
		i++;
	}
	return (result);
}

int	ft_isalpha(int c)
{
	if ('a' <= c && c <= 'z')
		return (1);
	else if ('A' <= c && c <= 'Z')
		return (1);
	else
		return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*tmp;

	tmp = 0;
	if (s1 != NULL && set != NULL)
	{
		start = 0;
		end = ft_strlen(s1);
		while (s1[start] && ft_strchr(set, s1[start]))
			start++;
		while (s1[end - 1] && ft_strchr(set, s1[end - 1]) && end > start)
			end--;
		if (end - start == 0)
			return (NULL);
		tmp = malloc(sizeof(char) * end - start + 1);
		if (tmp == NULL)
			return (0);
		if (tmp)
			ft_strlcpy(tmp, (char *)&s1[start], end - start + 1);
	}
	return (tmp);
}

void	shell_exit(t_info *info)
{
	free(info);
	rl_on_new_line();
	rl_redisplay();
	printf("exit\n");
	exit(g_exit_code);
}
