/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hj_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:31:37 by hojsong           #+#    #+#             */
/*   Updated: 2023/02/05 14:05:02 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./test.h"

char	**hj_split_cmd(char *str, char **envp)
{
	char	**spr;
	char	*sp;
	int		i[3];
	int		size;

	if (str == NULL)
		return (NULL);
	size = hj_mal_size(str, ' ');
	spr = malloc(sizeof(char *) * (size + 1));
	spr[size] = NULL;
	hj_array_zero(&i[0], &i[1], &i[2]);
	while (str[++i[2]])
	{
		if (str[i[2]] == '\'')
			i[2] += hj_compare_push(str, i[2], '\'');
		else if (str[i[2]] == '\"')
			i[2] += hj_compare_push(str, i[2], '\"');
		if (str[i[2]] != ' ' && (str[i[2] + 1] == ' ' || str[i[2] + 1] == '\0'))
		{
			sp = hj_str_save(str, i[2], i[0]);
			spr[i[1]++] = hj_split_join(sp, envp);
			free(sp);
			sp = NULL;
		}
		if (str[i[2]] == ' ')
			i[0] = i[2] + 1;
	}
	return (spr);
}

char	*hj_split_join(char *str, char **envp)
{
	char	**split;
	char	**split2;
	char	**split3;
	char	*result;
	int		size;

	size = hj_sp_mal_size(str);
	split = hj_save_split(str, size);
	split2 = hj_change_split(split, envp);
	split3 = hj_del_small(split2);
	result = hj_split_str_join(split3);
	all_free(split2);
	all_free(split3);
	return (result);
}

int	hj_isseting(int i, int *set, int count)
{
	int	idx;

	idx = 0;
	while (idx < count)
	{
		if (i == set[idx])
			return (0);
		idx++;
	}
	return (1);
}

void	hj_ft_error(void)
{
	printf("Error\n");
	exit(1);
}

int	hj_ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
		i++;
	return (i);
}
