/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 12:41:42 by hoslim            #+#    #+#             */
/*   Updated: 2023/02/06 15:32:35 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	hs_check_envp(char ***envp, char *str)
{
	int	i;

	i = 0;
	if (*envp == NULL)
		return (0);
	while ((*envp)[i])
	{
		if (!ft_strncmp((*envp)[i], str, ft_strlen(str)))
			return (1);
		i++;
	}
	return (0);
}
