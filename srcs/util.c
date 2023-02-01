/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:47:28 by hoslim            #+#    #+#             */
/*   Updated: 2023/02/01 19:30:55 by hoslim           ###   ########.fr       */
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
	info = malloc(sizeof(t_info));
	info->cmd = init_cmd();
	info->en = ft_calloc(len, sizeof(char *));
	i = -1;
	while (++i < len)
		info->en[i] = ft_strdup(envp[i]);
	info->en[i] = NULL;
	return (info);
}

t_cmd	*init_cmd(void)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	new->exec_flag = 0;
	new->parent_flag = 0;
	new->parse_flag = 0;
	new->type = 0;
	new->str = NULL;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

void	free_cmd(t_cmd *cmd, char *buf)
{
	if (buf)
		free(buf);
	if (cmd->str)
		free(cmd->str);
	cmd->exec_flag = 0;
	cmd->parent_flag = 0;
	cmd->parse_flag = 0;
	cmd->type = 0;
	if (cmd->left != NULL)
		free_cmd(cmd->left, NULL);
	if (cmd->right != NULL)
		free_cmd(cmd->right, NULL);
	if (cmd != NULL)
		free(cmd);
}

char	*parse_env_value(char *key, char ***envp)
{
	int		i;
	char	*parse;

	parse = NULL;
	i = -1;
	while ((*envp)[++i])
	{
		if (!ft_strncmp(key, (*envp)[i], ft_strlen(key)))
		{
			parse = ft_substr((*envp)[i], ft_strlen(key) + 1, \
			ft_strlen((*envp)[i]));
			break ;
		}
	}
	return (parse);
}

void	swap_env(char ***envp, char *src, char *key)
{
	int		i;
	char	*buf;

	i = -1;
	while ((*envp)[++i])
	{
		if (!ft_strncmp(key, (*envp)[i], ft_strlen(key)))
		{
			buf = (*envp)[i];
			(*envp)[i] = ft_strdup(src);
			free(buf);
			return ;
		}
	}
}

void	free_parse(char **str)
{
	int	i;
	int	len;

	i = 0;
	len = count_line(str);
	while (i < len)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	*hs_parsing_cmd(char ***envp, char *cmdline)
{
	char	*parsed;
	char	**path;

	path = pipe_parsing_envp(envp);
	parsed = pipe_parsing_cmd(path, cmdline);
	free_parse(path);
	return (parsed);
}

int	check_argc(char *str)
{
	int		ret;

	if (str && ft_isalpha(str[0]) == 1)
		ret = 0;
	else
		ret = 2;
	return (ret);
}
