/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 19:23:51 by hoslim            #+#    #+#             */
/*   Updated: 2023/02/05 14:31:31 by hoslim           ###   ########.fr       */
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
	hs_parse_redi_double(cmd);
}

void	hs_check_lexical(t_cmd *cmd, char *buf)
{
	if (check_type(cmd, buf) == T_WORD)
		return ;
	if (cmd->type == T_PIPE)
		hs_lexical_pipe(cmd, buf);
	else if (cmd->type == T_REDI)
		hs_lexical_redi(cmd, buf);
	if (cmd->left)
		hs_check_lexical(cmd->left, cmd->left->str);
	if (cmd->right)
		hs_check_lexical(cmd->right, cmd->right->str);
}

//여기서 누수 생기는데 나중에 해결 요함

void	parsing_cmd(t_info *info, char *buf)
{
	info->cmd = init_cmd();
	info->cmd->str = ft_strdup(buf);
	check_type(info->cmd, info->cmd->str);
	if (info->cmd->type != T_WORD)
		hs_check_lexical(info->cmd, buf);
}
