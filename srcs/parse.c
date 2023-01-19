/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 19:23:51 by hoslim            #+#    #+#             */
/*   Updated: 2023/01/19 19:11:55 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	hs_lexical_pipe(t_cmd *cmd, char *buf)
{
	int		i;
	int		idx;

	i = -1;
	idx = 0;
	while (buf[++i])
	{
		if (buf[i] == '|')
			idx = i;
	}
	hs_parse_pipe(cmd, buf, idx);
}

int	hs_check_redi(char *buf, char redi)
{
	int	i;

	i = -1;
	while (buf[++i])
	{
		if (buf[i] == redi)
		{
			if (buf[i + 1] == redi)
				i++;
			break ;
		}
	}
	if (buf[i] == '\0')
		return (-1);
	return (i);
}

void	hs_lexical_redi(t_cmd *cmd, char *buf)
{
	int		i;
	int		j;

	cmd->left = init_cmd();
	cmd->right = init_cmd();
	i = hs_check_redi(buf, '<');
	j = hs_check_redi(buf, '>');
	if (i != -1)
		hs_parse_redi(i, cmd, buf, 1);
	if (i == -1 && j != -1)
		hs_parse_redi(j, cmd, buf, 2);
}

void	hs_check_lexical(t_cmd *cmd, char *buf)
{
	if (buf == NULL || check_type(cmd, buf) == T_WORD)
		return ;
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
