/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hs_parse_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosunglim <hosunglim@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 12:42:56 by hoslim            #+#    #+#             */
/*   Updated: 2023/01/18 23:27:42 by hosunglim        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	hs_lexical_parse(t_cmd *cmd, char *buf, int i)
{
	char	*left_str;
	char	*right_str;

	cmd->left = ft_calloc(1, sizeof(t_cmd));
	cmd->right = ft_calloc(1, sizeof(t_cmd));
	left_str = ft_substr(buf, 0, i);
	right_str = ft_substr(buf, i + 1, ft_strlen(buf) - i);
	cmd->left->str = ft_strdup(left_str);
	cmd->right->str = ft_strdup(right_str);
}

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
