/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 20:37:53 by hosunglim         #+#    #+#             */
/*   Updated: 2023/01/26 17:20:51 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//1. 인자의 갯수를 파악하고 2개 이상이면 나머지 문자열을 받고 에러를 출력
//2. 인자의 갯수가 맞다면 파싱 후 키값에 숫자가 있는지 파악
//과연 구조체 내로 복사한 환경변수에 값을 넣어야 하는지
//그 값을 어떻게 사용해야 하는가

int	check_argc(char *str)
{
	char	**temp;
	char	**key;
	int		i;

	temp = ft_split(str, ' ');
	key = ft_split(temp[1], '=');
	i = 0;
	while (temp[i])
		i++;
	free(temp[0]);
	free(temp[1]);
	free(temp);
	if (i > 2)
		return (1);
	if (ft_isdigit(key[0][0]) == 1)
	{
		free(key[0]);
		free(key[1]);
		return (2);
	}
	free(key[0]);
	free(key[1]);
	free(key);
	return (0);
}

void	export_error(t_cmd *cmd, int flag)
{
	char	**temp;
	int		i;

	if (flag == 0)
		return ;
	if (flag == 1)
	{
		i = 1;
		temp = ft_split(cmd->str, ' ');
		while (temp[++i])
			write(2, "not a valid identifier\n", 23);
	}
	else if (flag == 2)
		error(NULL, "minishell: export: not a valid indentifer\n");
	else if (flag == 3)
	{
		write(2, "not a valid identifier\n", 23);
		i = 1;
		temp = ft_split(cmd->str, ' ');
		while (temp[++i])
			write(2, "not a valid identifier\n", 23);
	}
}

void	ft_export(t_cmd *cmd, char **envp)
{
	int		len;
	char	**parsed;

	export_error(cmd, check_argc(cmd->str));
	parsed = ft_split(cmd->str, ' ');
	// if (parsed[1] == NULL)
	// 	export_declare(envp);
	len = 0;
	while (envp[len])
		len++;
	envp[len] = ft_strdup(parsed[1]);
	envp[len + 1] = NULL;
	free(parsed[0]);
	free(parsed[1]);
	free(parsed);
}
