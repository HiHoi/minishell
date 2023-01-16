/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 19:23:51 by hoslim            #+#    #+#             */
/*   Updated: 2023/01/15 21:23:29 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_line(char **line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	return (i);
}

void	check_type(t_cmd *cmd, char *buf)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == '|')
		{
			cmd->type = T_PIPE;
			break ;
		}
		else if (buf[i] == '<' || buf[i] == '>')
		{
			cmd->type = T_REDI;
			break ;
		}
		else
			cmd->type = T_WORD;
		buf++;
	}
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
		printf("%d %s\n", i, line[i]);
		cur->str = ft_strdup(line[i]);
		printf("%s\n", cur->str);
		check_type(cur, line[i]);
		cur->right = ft_calloc(1, sizeof(t_cmd));
		cur = cur->right;
	}
}

void	parsing_cmd(t_info *info, char *buf)
{
	char	**line;

	line = ft_split(buf, '|');
	info->cmd = ft_calloc(1, sizeof(t_cmd));
	info->cmd->str = ft_strdup(buf);
	check_type(info->cmd, buf);
	info->cmd->left = ft_calloc(1, sizeof(t_cmd));
	info->cmd->left->str = ft_strdup(line[0]);
	check_type(info->cmd->left, info->cmd->left->str);
	
	split_cmd(&info, line);

	printf("________________________________\n");
	printf("%s\n", info->cmd->str);
	t_cmd	*left_cur = info->cmd->left;
	while (left_cur)
	{
		printf("left : %s\n", left_cur->str);
		left_cur = left_cur->left;
	}
	t_cmd *right_cur = info->cmd->right;
	while (right_cur)
	{
		printf("right : %s\n", right_cur->str);
		right_cur = right_cur->right;
	}
	// info->program->cmd->token = malloc(sizeof(t_token) * count_line(line));
	// if (!info->program->cmd->token)
	// 	error(info, "Wrong cmd");
	//lexical
	//syntax
}
