/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 12:39:44 by hoslim            #+#    #+#             */
/*   Updated: 2023/02/06 12:41:04 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (*(src + i))
	{
		*(dest + i) = *(src + i);
		i++;
	}
	*(dest + i) = '\0';
	return (dest);
}

char	*ft_strdup(const char *src)
{
	int		i;
	char	*tmp;

	if (src == NULL)
		return (NULL);
	i = ft_strlen(src) + 1;
	tmp = (char *)malloc(sizeof(char) * i);
	if (tmp == NULL)
		return (0);
	ft_strcpy(tmp, src);
	return (tmp);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		s1_len;
	int		s2_len;
	char	*tmp;

	i = -1;
	j = -1;
	if (s1 == NULL)
		return (0);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	tmp = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (tmp == NULL)
		return (0);
	while (s1[++i])
		tmp[i] = s1[i];
	while (s2[++j])
		tmp[i + j] = s2[j];
	tmp[i + j] = '\0';
	return (tmp);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*rlt;

	if (!s)
		return (NULL);
	if ((unsigned int)ft_strlen(s) < start || len == 0 || s[start] == '\0')
		return (NULL);
	s_len = ft_strlen((char *)(s + start));
	if (ft_strlen(s) < len)
		len = ft_strlen(s);
	if (len > s_len)
		len = s_len;
	rlt = (char *)malloc(sizeof(char) * (len + 1));
	if (rlt == NULL)
		return (0);
	ft_strlcpy(rlt, (char *)(s + start), len + 1);
	return (rlt);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (*(s1 + i) == *(s2 + i))
	{
		if (*(s1 + i) == '\0')
			return (0);
		i++;
	}
	return (*(s1 + i) - *(s2 + i));
}
