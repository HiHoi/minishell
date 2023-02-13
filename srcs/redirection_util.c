/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:17:52 by hoslim            #+#    #+#             */
/*   Updated: 2023/02/13 16:58:23 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_exit_code;

int	count_redi(t_cmd *cmd)
{
	t_cmd	*cur;
	int		count;

	cur = cmd;
	count = 0;
	while (cur)
	{
		if (cur->type == T_REDI)
			count++;
		cur = cur->right;
	}
	return (count);
}

void	redi_pipe(t_cmd *cmd, char ***envp)
{
	hs_redirect(cmd->left, envp);
	hs_redirect(cmd->right, envp);
	hs_cmd(cmd->left->left, envp);
}
