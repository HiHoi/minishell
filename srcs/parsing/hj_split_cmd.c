/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hj_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:31:37 by hojsong           #+#    #+#             */
/*   Updated: 2023/02/14 14:01:57 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./test.h"

extern int	g_exit_code;

char	**hj_split_cmd(char *str, char **envp)
{
	char	**spr;
	char	*sp;
	int		i[3];

	spr = hj_set_int(str, i);
	if (spr == NULL)
		return (0);
	while (str[i[0]])
	{
		if (str[i[0]] == '\'')
			i[0] += hj_compare_push(str, i[0], '\'');
		else if (str[i[0]] == '\"')
			i[0] += hj_compare_push(str, i[0], '\"');
		if (str[i[0]] != ' ' && (str[i[0] + 1] == ' ' || str[i[0] + 1] == '\0'))
		{
			sp = hj_str_save(str, i[0], i[1]);
			spr[i[2]++] = hj_split_join(sp, envp);
			free(sp);
			sp = NULL;
		}
		if (str[i[0]] == ' ')
			i[1] = i[0] + 1;
		i[0]++;
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
	split3 = hj_del_small(split2, size);
	result = hj_split_str_join(split3, size);
	all_free(split2, size);
	all_free(split3, size);
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
	write(2, "minishell: not paired queto\n", 29);
	g_exit_code = 1;
	exit(g_exit_code);
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
