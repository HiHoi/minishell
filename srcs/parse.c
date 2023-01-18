/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosunglim <hosunglim@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 19:23:51 by hoslim            #+#    #+#             */
/*   Updated: 2023/01/18 23:42:54 by hosunglim        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	hs_lexical_pipe(t_cmd *cmd, char *buf)
{
	int		i;

	i = -1;
	while (buf[++i])
	{
		if (buf[i] == '|')
			break ;
	}
	hs_lexical_parse(cmd, buf, i);
}

void	hs_lexical_redi(t_cmd *cmd, char *buf)
{
	int		i;
	char	**line;
	char	*file;

	line = ft_split(buf, ' ');
	cmd->left = ft_calloc(1, sizeof(t_cmd));
	cmd->right = ft_calloc(1, sizeof(t_cmd));
	if (!ft_strcmp(line[0], "<") || !ft_strcmp(line[0], "<<") || !ft_strcmp(line[0], ">") \
	|| !ft_strcmp(line[0], ">>"))
	{
		cmd->left->str = ft_strdup(line[1]);
		if (line[2])
			cmd->right->str = ft_strdup(line[2]);
	}
	else
	{
		i = -1;
		while (line[0][++i])
		{
			if (line[0][i] == '>' || line[0][i] == '<')
			{
				if (line[0][i + 1] == '>' || line[0][i + 1] == '<')
					i++;
				break ;
			}
		}
		file = ft_substr(line[0], i + 1, ft_strlen(line[0]) - i + 1);
		cmd->left->str = ft_strdup(file);
		if (line[1])
			cmd->right->str = ft_strdup(line[1]);
	}
}

void	hs_check_lexical(t_cmd *cmd, char *buf)
{
	if (buf == NULL || check_type(cmd, buf) == T_WORD)
	{
		printf("%s\n", cmd->str);
		return ;
	}
	if (check_type(cmd, buf) == T_PIPE)
		hs_lexical_pipe(cmd, buf);
	else if (check_type(cmd, buf) == T_REDI)
		hs_lexical_redi(cmd, buf);
	if (cmd->left != NULL)
		hs_check_lexical(cmd->left, cmd->left->str);
	if (cmd->right != NULL)
		hs_check_lexical(cmd->right, cmd->right->str);
}

void	parsing_cmd(t_info *info, char *buf)
{
	check_type(info->cmd, buf);
	info->cmd->str = ft_strdup(buf);
	if (info->cmd->type != T_WORD)
		hs_check_lexical(info->cmd, buf);
}
