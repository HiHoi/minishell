/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 20:37:53 by hosunglim         #+#    #+#             */
/*   Updated: 2023/02/14 16:49:02 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**sort_envp(char **envp)
{
	int		i[2];
	int		len;
	char	*buf;
	char	**sorted;

	i[0] = -1;
	len = count_line(envp);
	while (++i[0] < len - 1)
	{
		i[1] = i[0] + 1;
		if (ft_strcmp(envp[i[0]], envp[i[1]]) > 0)
		{
			buf = envp[i[0]];
			envp[i[0]] = envp[i[1]];
			envp[i[1]] = buf;
		}
	}
	sorted = malloc(sizeof(char *) * (len + 1));
	if (!sorted)
		return (0);
	i[0] = -1;
	while (++i[0] < len)
		sorted[i[0]] = ft_strdup(envp[i[0]]);
	sorted[len] = NULL;
	return (sorted);
}

void	export_declare(char **envp)
{
	int		i;
	char	**sorted;
	char	**parse;

	sorted = sort_envp(envp);
	i = -1;
	while (envp[++i])
	{
		parse = hj_envp_bigtaging(envp[i]);
		if (parse[1][0] != '\0')
			printf("declare -x %s=\"%s\"\n", parse[0], parse[1]);
		else if (parse[0])
			printf("declare -x %s\n", parse[0]);
		free_parse(parse);
		free(sorted[i]);
	}
	free(sorted);
}

int	export_error(char *str)
{
	int		flag;

	flag = check_argc(str);
	if (flag == 0)
		return (flag);
	else if (flag == 2)
	{
		write(2, "minishell: export: ", 20);
		write(2, str, ft_strlen(str));
		write(2, ": not a valid indentifer\n", 26);
	}
	return (flag);
}

char	**check_export(char **parse)
{
	int		idx;
	int		len;
	int		idx_ret;
	char	**ret;

	len = count_line(parse);
	ret = malloc(sizeof(char *) * (len + 1));
	if (ret == NULL)
		return (NULL);
	idx = -1;
	idx_ret = 0;
	while (parse[++idx])
	{
		if (hj_envp_name_chk(parse[idx]) == 1)
			export_error(parse[idx]);
		else
			ret[idx_ret++] = ft_strdup(parse[idx]);
	}
	ret[idx_ret] = NULL;
	return (ret);
}

void	ft_export(t_cmd *cmd, char ***envp)
{
	char	**new;
	char	*test;
	char	**admit;
	char	**parsed;

	cmd->exec_flag = 1;
	test = ft_strtrim(cmd->str, " ");
	if (ft_strcmp(test, "export") == 0)
		export_declare(*envp);
	else
	{
		parsed = hj_split_cmd(cmd->str, *envp);
		admit = check_export(parsed);
		if (admit != NULL)
		{
			new = hj_export_insert(admit, *envp);
			free_parse(*envp);
			*envp = new;
			free_parse(admit);
		}
		free_parse(parsed);
	}
	free(test);
}
