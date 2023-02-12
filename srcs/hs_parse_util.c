/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hs_parse_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 12:42:56 by hoslim            #+#    #+#             */
/*   Updated: 2023/02/12 20:33:55 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	hs_parse_redi_trim(t_cmd *cmd, char	**cmd_file)
{
	cmd->left->str = ft_strdup(cmd_file[1]);
	cmd->right->str = ft_strdup(cmd_file[0]);
}

void	hs_parse_redi(int idx, t_cmd *cmd, char *buf, int flag)
{
	char	**cmd_file;

	if (flag == 1)
	{
		cmd->right->str = ft_substr(buf, idx + 1, ft_strlen(buf) - idx);
		cmd_file = ft_split(cmd->right->str, ' ');
		if (cmd_file && cmd_file[1])
			hs_parse_redi_trim(cmd, cmd_file);
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

int	check_queto(int *i, int ret, char *buf, char queto)
{
	int	idx;

	idx = 1;
	while (buf[*i + idx] != '\0' && buf[*i + idx] != queto)
		idx++;
	*i += idx;
	if (ret == T_WORD)
		ret = T_WORD;
	return (ret);
}

int	check_type(t_cmd *cmd, char *buf)
{
	int	i[2];

	i[1] = T_WORD;
	if (buf == NULL)
	{
		cmd->type = T_WORD;
		return (T_WORD);
	}
	i[0] = -1;
	while (buf[++i[0]] != '\0')
	{
		if (buf[i[0]] == '|')
		{
			cmd->type = T_PIPE;
			return (T_PIPE);
		}
		else if (buf[i[0]] == '<' || buf[i[0]] == '>')
			i[1] = T_REDI;
		else if (buf[i[0]] == '\"')
			i[1] = check_queto(&i[0], i[1], buf, '\"');
		else if (buf[i[0]] == '\'')
			i[1] = check_queto(&i[0], i[1], buf, '\'');
	}
	cmd->type = i[1];
	return (i[1]);
}
