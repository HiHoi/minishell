/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hs_parse_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 12:42:56 by hoslim            #+#    #+#             */
/*   Updated: 2023/02/05 14:32:21 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	hs_parse_pipe(t_cmd *cmd, char *buf, int i)
{
	char	*left_str;
	char	*right_str;

	cmd->left = init_cmd();
	cmd->right = init_cmd();
	left_str = ft_substr(buf, 0, i);
	right_str = ft_substr(buf, i + 1, ft_strlen(buf) - i);
	cmd->left->str = ft_strdup(left_str);
	cmd->right->str = ft_strdup(right_str);
	free(left_str);
	free(right_str);
}

void	hs_parse_redi_double(t_cmd *cmd)
{
	char	*parse;
	char	*tmp;

	if (ft_strchr(cmd->left->str, '>'))
	{
		parse = ft_strtrim(cmd->left->str, ">");
		tmp = cmd->left->str;
		cmd->left->str = ft_strdup(parse);
		free(parse);
		free(tmp);
	}
	if (ft_strchr(cmd->left->str, '<'))
	{
		parse = ft_strtrim(cmd->left->str, "<");
		tmp = cmd->left->str;
		cmd->left->str = ft_strdup(parse);
		cmd->left->exec_flag = 1;
		free(parse);
		free(tmp);
	}
}

void	hs_parse_redi_trim(t_cmd *cmd, char	*left, char *right)
{
	cmd->left->str = ft_strdup(left);
	cmd->right->str = ft_strdup(right);
}

void	hs_parse_redi(int idx, t_cmd *cmd, char *buf, int flag)
{
	char	**cmd_file;

	if (flag == 1)
	{
		cmd->right->str = ft_substr(buf, idx + 1, ft_strlen(buf) - idx);
		cmd_file = ft_split(cmd->right->str, ' ');
		if (cmd_file && cmd_file[1])
			hs_parse_redi_trim(cmd, cmd_file[1], cmd_file[0]);
		else
		{
			if (idx == 0)
				cmd->left->str = NULL;
			else
				cmd->left->str = ft_substr(buf, 0, idx);
		}
		free_parse(cmd_file);
	}
	else if (flag == 2)
	{
		cmd->left->str = ft_substr(buf, 0, idx);
		if (idx == (int)ft_strlen(buf) - 1)
			cmd->right->str = NULL;
		else
			cmd->right->str = ft_substr(buf, idx + 1, ft_strlen(buf) - idx);
	}
}

int	check_type(t_cmd *cmd, char *buf)
{
	int	i;
	int	ret;

	i = 0;
	ret = T_WORD;
	if (buf == NULL)
	{
		cmd->type = ret;
		return (ret);
	}
	while (buf[i])
	{
		if (buf[i] == '|')
		{
			cmd->type = T_PIPE;
			return (T_PIPE);
		}
		else if (buf[i] == '<' || buf[i] == '>')
			ret = T_REDI;
		i++;
	}
	cmd->type = ret;
	return (ret);
}
