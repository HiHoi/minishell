/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 20:37:53 by hosunglim         #+#    #+#             */
/*   Updated: 2023/02/09 16:31:14 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	export_error(char *str)
{
	int		flag;

	flag = check_argc(str);
	if (flag == 0)
		return (flag);
	else if (flag == 2)
		write(2, "minishell: export: not a valid indentifer\n", 42);
	return (flag);
}

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
	sorted = ft_calloc(len, sizeof(char *));
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
		printf("declare -x %s=\"%s\"\n", parse[0], parse[1]);
		free_parse(parse);
		free(sorted[i]);
	}
	free(sorted);
}

//중복처리

char	**export_insert(char **str, char ***envp, int key_len, int envp_len)
{
	int		j;
	int		i;
	char	**new;

	new = malloc(sizeof(char *) * (key_len + envp_len));
	if (!new)
		return (NULL);
	i = -1;
	j = 1;
	while (++i < envp_len + key_len)
	{
		if (i >= envp_len && j < key_len)
		{
			if (export_error(str[j]) == 0)
				new[i] = ft_strdup(str[j]);
			else
				i--;
			j++;
		}
		else if (i < envp_len)
			new[i] = ft_strdup((*envp)[i]);
	}
	new[i] = NULL;
	return (new);
}

void	ft_export(t_cmd *cmd, char ***envp)
{
	int		parsed_len;
	int		envp_len;
	char	**new;
	char	**parsed;

	cmd->exec_flag = 1;
	if (ft_strcmp(cmd->str, "export") == 0)
	{
		export_declare(*envp);
		return ;
	}
	else if (ft_strchr(cmd->str, '=') == 0)
		return ;
	parsed = hj_split_cmd(cmd->str, *envp);
	parsed_len = count_line(parsed);
	envp_len = count_line(*envp);
	new = export_insert(parsed, envp, parsed_len, envp_len);
	free_parse(*envp);
	*envp = new;
	free_parse(parsed);
}
