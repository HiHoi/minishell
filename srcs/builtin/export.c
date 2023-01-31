/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 20:37:53 by hosunglim         #+#    #+#             */
/*   Updated: 2023/01/30 17:33:33 by hoslim           ###   ########.fr       */
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
	if (i > 1)
		return (1);
	if (ft_isdigit(key[0][0]) == 1 || key[1] == NULL)
	{
		free(key[0]);
		free(key[1]);
		free(key);
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

	i = 1;
	if (flag == 0)
		return ;
	if (flag == 1)
	{
		temp = ft_split(cmd->str, ' ');
		while (++i < count_line(temp))
			write(2, "not a valid identifier\n", 23);
	}
	else if (flag == 2)
		write(2, "minishell: export: not a valid indentifer\n", 42);
	else if (flag == 3)
	{
		write(2, "not a valid identifier\n", 23);
		temp = ft_split(cmd->str, ' ');
		while (++i < count_line(temp))
			write(2, "not a valid identifier\n", 23);
	}
}

char	**sort_envp(char **envp)
{
	int		i;
	int		j;
	int		len;
	char	*buf;
	char	**sorted;

	i = -1;
	len = count_line(envp);
	while (++i < len - 1)
	{
		j = i + 1;
		if (ft_strcmp(envp[i], envp[j]) > 0)
		{
			buf = envp[i];
			envp[i] = envp[j];
			envp[j] = buf;
		}
	}
	sorted = ft_calloc(len, sizeof(char *));
	i = -1;
	while (++i < len)
		sorted[i] = ft_strdup(envp[i]);
	sorted[len] = NULL;
	return (sorted);
}

void	export_declare(char **envp)
{
	int		i;
	char	**sorted;

	sorted = sort_envp(envp);
	i = -1;
	while (envp[++i])
	{
		write(1, "declare -x ", 11);
		write(1, sorted[i], ft_strlen(sorted[i]));
		write(1, "\n", 1);
		free(sorted[i]);
	}
	free(sorted);
}

//expr echo 가 작동되지 않음
//추가시 대문자는 정렬
// 소문자는 찾아봐야함
//declare시 대문자 소문자 순서로 오름차순으로 정렬
//key만 있을때 처리
//여러 개의 키와 밸류도 같이 실행

void	ft_export(t_cmd *cmd, char ***envp)
{
	int		len;
	int		i;
	char	**new;
	char	**parsed;

	if (ft_strchr(cmd->str, ' ') == 0)
	{
		export_declare(*envp);
		return ;
	}
	export_error(cmd, check_argc(cmd->str));
	parsed = ft_split(cmd->str, ' ');
	len = count_line(*envp);
	new = malloc(sizeof(char *) * (len + 1));
	i = -1;
	while ((*envp)[++i])
		new[i] = ft_strdup((*envp)[i]);
	new[i] = ft_strdup(parsed[1]);
	new[i + 1] = NULL;
	*envp = new;
}
