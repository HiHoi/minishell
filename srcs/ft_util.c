/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:35:04 by hoslim            #+#    #+#             */
/*   Updated: 2023/02/03 15:12:48 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strchr(const char *str, int c)
{
	char	find;
	int		i;

	if (str == NULL)
		return (0);
	i = 0;
	find = (unsigned char)c;
	while (str[i])
	{
		if (str[i] == find)
			return ((char *)&str[i]);
		i++;
	}
	if (str[i] == find)
		return ((char *)&str[i]);
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n && *(s1 + i) == *(s2 + i))
	{
		if (*(s1 + i) == '\0')
			return (0);
		i++;
	}
	if (i == n)
		return (0);
	return ((unsigned char)*(s1 + i) - (unsigned char)*(s2 + i));
}

void	*ft_memset(void *ptr, int value, size_t num)
{
	size_t			i;
	unsigned char	*tmp;

	i = 0;
	tmp = (unsigned char *)ptr;
	while (i < num)
		tmp[i++] = (unsigned char)value;
	return (tmp);
}

size_t	ft_strlen(const char *str)
{
	int	cnt;

	if (str == NULL)
		return (0);
	cnt = 0;
	while (*(str + cnt))
		cnt++;
	return (cnt);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	len;

	i = 0;
	len = ft_strlen(src);
	if (size == 0)
		return (len);
	while (i < len && (i + 1) < size)
	{
		*(dest + i) = *(src + i);
		i++;
	}
	if (size > 0)
		*(dest + i) = '\0';
	return (len);
}

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
	if ((unsigned int)ft_strlen(s) < start || len == 0)
		return (ft_strdup(""));
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

int	itoa_len(int n)
{
	int	cnt;

	cnt = 0;
	if (n < 0)
		cnt = 1;
	if (n == 0)
		cnt = 1;
	while (n)
	{
		cnt++;
		n = n / 10;
	}
	return (cnt);
}

void	swap(char *c1, char *c2)
{
	char	t;

	t = *c1;
	*c1 = *c2;
	*c2 = t;
}

char	*reverse(char *rlt, int i, int j)
{
	while (i < j)
		swap(&rlt[i++], &rlt[j--]);
	return (rlt);
}

char	*ft_itoa(int n)
{
	char		*rlt;
	long long	nbr;
	int			i;
	int			round;

	i = 0;
	nbr = (long long)n;
	round = itoa_len(nbr);
	if (nbr < 0)
		nbr *= -1;
	rlt = malloc(sizeof(char) * round + 1);
	if (rlt == NULL)
		return (0);
	if (n == 0)
		rlt[i++] = '0';
	while (nbr)
	{
		rlt[i++] = nbr % 10 + '0';
		nbr = nbr / 10;
	}
	if (n < 0)
		rlt[i++] = '-';
	rlt[i] = '\0';
	return (reverse(rlt, 0, i - 1));
}

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
