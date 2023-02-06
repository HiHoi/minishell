/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 21:35:20 by hoslim            #+#    #+#             */
/*   Updated: 2023/02/06 11:54:40 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*ft_calloc(size_t nelem, size_t elsize)
{
	unsigned char	*tmp;
	size_t			i;

	tmp = malloc(elsize * nelem);
	if (!tmp)
		error(NULL, "Failed to malloc\n", -1);
	i = 0;
	while (i < elsize)
		tmp[i++] = 0;
	return (tmp);
}

char	**freeall(char **s)
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

size_t	word_cnt(const char *s, char c)
{
	size_t	cnt;
	size_t	i;

	if (s == NULL)
		return (0);
	cnt = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			cnt++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (cnt);
}

char	*worddup(const char *s, char c)
{
	size_t	len;
	char	*ptr;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	ptr = ft_calloc(len + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s, len + 1);
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	char	**tmp;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	tmp = (char **)ft_calloc((size_t)word_cnt(s, c) + 1, sizeof(char *));
	if (!tmp || !s)
		return (NULL);
	while (i < (size_t)word_cnt(s, c) && s[j])
	{
		if (s[j] != c)
		{
			tmp[i] = worddup(&s[j], c);
			if (!tmp[i++])
				return (freeall(tmp));
			while (s[j] && s[j] != c)
				j++;
		}
		else
			j++;
	}
	tmp[i] = NULL;
	return (tmp);
}
