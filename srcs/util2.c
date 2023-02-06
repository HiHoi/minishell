/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 12:44:18 by hoslim            #+#    #+#             */
/*   Updated: 2023/02/06 12:45:32 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*init_cmd(void)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd) * 1);
	new->exec_flag = 0;
	new->parent_flag = 0;
	new->parse_flag = 0;
	new->type = 0;
	new->str = NULL;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

void	free_cmd(t_cmd *cmd, char *buf)
{
	if (buf)
		free(buf);
	if (cmd->str)
		free(cmd->str);
	cmd->exec_flag = 0;
	cmd->parent_flag = 0;
	cmd->parse_flag = 0;
	cmd->type = 0;
	if (cmd->left != NULL)
		free_cmd(cmd->left, NULL);
	if (cmd->right != NULL)
		free_cmd(cmd->right, NULL);
	if (cmd != NULL)
	{
		free(cmd);
		return ;
	}
}

char	*parse_env_value(char *key, char ***envp)
{
	int		i;
	char	*parse;

	parse = NULL;
	i = -1;
	while ((*envp)[++i])
	{
		if (!ft_strncmp(key, (*envp)[i], ft_strlen(key)))
		{
			parse = ft_substr((*envp)[i], ft_strlen(key) + 1, \
			ft_strlen((*envp)[i]));
			break ;
		}
	}
	return (parse);
}

void	swap_env(char ***envp, char *src, char *key)
{
	int		i;
	char	*buf;

	i = -1;
	while ((*envp)[++i])
	{
		if (!ft_strncmp(key, (*envp)[i], ft_strlen(key)))
		{
			buf = (*envp)[i];
			(*envp)[i] = ft_strdup(src);
			free(buf);
			return ;
		}
	}
}

void	free_parse(char **str)
{
	int	i;
	int	len;

	i = 0;
	len = count_line(str);
	while (i < len)
	{
		free(str[i]);
		i++;
	}
	free(str);
}
