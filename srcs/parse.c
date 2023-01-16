/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 19:23:51 by hoslim            #+#    #+#             */
/*   Updated: 2023/01/16 20:27:29 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_type(t_cmd *cmd, char *buf)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == '|')
		{
			cmd->type = T_PIPE;
			return (T_PIPE);
		}
		else if (buf[i] == '<' || buf[i] == '>')
		{
			cmd->type = T_REDI;
			return (T_REDI);
		}
		else
			cmd->type = T_WORD;
		buf++;
	}
	return (T_WORD);
}

void	split_cmd(t_info **info, char **line)
{
	t_cmd	*cur;
	int		i;

	i = 0;
	(*info)->cmd->right = ft_calloc(1, sizeof(t_cmd));
	cur = (*info)->cmd->right;
	while (line[++i])
	{
		cur->str = ft_strdup(line[i]);
		check_type(cur, line[i]);
		cur->right = ft_calloc(1, sizeof(t_cmd));
		cur = cur->right;
	}
}

void	hs_lexical_pipe(t_cmd *cmd, char *buf)
{
	int		i;
	char	*left_str;
	char	*right_str;

	i = -1;
	while (buf[++i])
	{
		if (buf[i] == '|')
			break ;
	}
	cmd->left = ft_calloc(1, sizeof(t_cmd));
	left_str = ft_substr(buf, 0, i);
	cmd->left->str = ft_strdup(left_str);
	cmd->right = ft_calloc(1, sizeof(t_cmd));
	right_str = ft_substr(buf, i + 1, ft_strlen(buf) - i);
	cmd->right->str = ft_strdup(right_str);
}

void	hs_lexical_redi(t_cmd *cmd, char *buf)
{
	int		i;
	char	*left_str;
	char	*right_str;

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
	cmd->left = ft_calloc(1, sizeof(t_cmd));
	left_str = ft_substr(buf, 0, i);
	cmd->left->str = ft_strdup(left_str);
	cmd->right = ft_calloc(1, sizeof(t_cmd));
	right_str = ft_substr(buf, i + 1, ft_strlen(buf) - i);
	cmd->right->str = ft_strdup(right_str);
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
