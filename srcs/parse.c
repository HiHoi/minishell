/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 19:23:51 by hoslim            #+#    #+#             */
/*   Updated: 2023/01/17 12:46:59 by hoslim           ###   ########.fr       */
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

	i = -1;
	while (buf[++i])
	{
		if (buf[i] == '<')
		{
			if (buf[i + 1] == '<')
				i++;
			break ;
		}
		else if (buf[i] == '>')
		{
			if (buf[i + 1] == '>')
				i++;
			break ;
		}
	}
	hs_lexical_parse(cmd, buf, i);
}

void	hs_check_lexical(t_cmd *cmd, char *buf)
{
	if (check_type(cmd, buf) == T_WORD)
		return ;
	else if (check_type(cmd, buf) == T_PIPE)
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
	if (info->cmd->type != T_WORD)
		hs_check_lexical(info->cmd, buf);
	else
		info->cmd->str = ft_strdup(buf);
}
