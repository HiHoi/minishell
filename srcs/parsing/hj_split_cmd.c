/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hj_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:31:37 by hojsong           #+#    #+#             */
/*   Updated: 2023/02/02 21:02:39 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./test.h"

char	**hj_split_cmd(char *str, char **envp)
{
	char	**spr;
	char	*sp;
	int 	i;
	int		i2;
	int		j;
	int		size;

	size = hj_mal_size(str, ' ');
	spr = malloc(sizeof(char *) * (size + 1));
	spr[size] = NULL;
	j = 0;
	i2 = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			i += hj_compare_push(str, i, '\'');
		else if (str[i] == '\"')
			i += hj_compare_push(str, i, '\"');
		if (str[i] != ' ' && (str[i + 1] == ' ' || str[i + 1] == '\0'))
		{
			sp = hj_str_save(str, i, j);
			spr[i2] = hj_split_join(sp, envp);
			free(sp);
			sp = NULL;
			i2++;
		}
		if (str[i] == ' ')
			j = i + 1;
		i++;
	}
	return (spr);
}

char	*hj_split_join(char *str, char **envp)
{
	char	**split;
	char	**split2;
	char	*result;
	int		size;
	int		chk;

	chk = hj_check_small(str);
	size = hj_sp_mal_size(str);
	split = hj_save_split(str, size);
	split2 = hj_change_split(split, envp);
	result = hj_split_str_join(split2);
	all_free(split2);
	if (chk == 0)
		return (result);
	return (hj_del_small(result));
}

int	hj_isseting(int i, int *set, int count)
{
	int idx;

	idx = 0;
	while (idx < count)
	{
		if (i == set[idx])
			return (0);
		idx++;
	}
	return (1);
}

void	ft_error(void)
{
	printf("Error\n");
	exit(1);
}

int	hj_ft_strlen(char *str)
{
	int i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
		i++;
	return (i);
}
