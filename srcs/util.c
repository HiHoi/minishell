/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosunglim <hosunglim@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:47:28 by hoslim            #+#    #+#             */
/*   Updated: 2023/01/29 14:58:36 by hosunglim        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exit_code;

int	count_line(char **line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	return (i);
}

void	free_info(t_info *info)
{
	//글자 프리 필요
	if (info->cmd)
		free(info->cmd);
	if (info)
		free(info);
}

int	error(t_info *info, char *s)
{
	if (info)
		free_info(info);
	if (s)
		write(2, s, ft_strlen(s));
	exit(exit_code);
}

int	hs_error_return(t_info *info, t_cmd *cmd, char *s)
{
	if (info)
		free_info(info);
	if (cmd)
		free(cmd);
	if (s)
		write(2, s, ft_strlen(s));
	exit_code = 127;
	return (exit_code);
}

t_info	*init_info(char **envp)
{
	t_info	*info;
	int		i;
	int		len;

	len = count_line(envp);
	info = ft_calloc(1, sizeof(t_info));
	info->cmd = init_cmd();
	info->en = ft_calloc(len, sizeof(char *));
	i = -1;
	while (++i < len)
		info->en[i] = ft_strdup(envp[i]);
	info->en[len] = NULL;
	return (info);
}

t_cmd	*init_cmd(void)
{
	t_cmd	*new;

	new = ft_calloc(1, sizeof(t_cmd));
	new->exec_flag = 0;
	new->parent_flag = 0;
	new->parse_flag = 0;
	new->type = 0;
	new->str = NULL;
	return (new);
}

void	free_cmd(t_cmd *cmd)
{
	if (cmd->str)
		free(cmd->str);
	cmd->exec_flag = 0;
	cmd->parent_flag = 0;
	cmd->parse_flag = 0;
	cmd->type = 0;
	if (!cmd->left && !cmd->right && cmd)
		free(cmd);
	if (cmd->left != NULL)
		free_cmd(cmd->left);
	if (cmd->right != NULL)
		free_cmd(cmd->right);
}
