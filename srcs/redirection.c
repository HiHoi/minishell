/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:24:23 by hoslim            #+#    #+#             */
/*   Updated: 2023/02/09 21:47:34 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redi_input(t_cmd *cmd)
{
	int		in;
	char	*path;

	path = ft_strtrim(cmd->left->right->str, " ");
	in = open(path, O_RDONLY | O_EXCL, 0644);
	if (in < 0)
		error(NULL, path, 1);
	dup2(in, STDIN_FILENO);
	close(in);
}

void	redi_output(t_cmd *cmd)
{
	int		out;
	char	*path;

	path = ft_strtrim(cmd->left->right->str, " ");
	out = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (out < 0)
		error(NULL, path, 1);
	dup2(out, STDOUT_FILENO);
	close(out);
}

//ls -l|cat |  cat << end | wc -l => 2
//ls -l|cat |  << end | wc -l => 0

void	redi_heredoc(t_cmd *cmd)
{
	int		in;

	(void)cmd;
	in = open("/tmp/.temp_file", O_RDONLY | O_EXCL, 0644);
	if (in < 0)
		error(NULL, "/tmp/.temp_file", 1);
	dup2(in, STDIN_FILENO);
	close(in);
}

void	redi_append(t_cmd *cmd)
{
	int		out;
	char	*path;

	path = ft_strtrim(cmd->left->right->str, " ");
	out = open(path, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (out < 0)
		error(NULL, path, 1);
	dup2(out, STDOUT_FILENO);
	close(out);
}

void	hs_redirect(t_cmd *cmd)
{
	int	i;

	i = -1;
	while (cmd->str[++i])
	{
		if (cmd->str[i] == '<')
		{
			if (cmd->str[i + 1] == '<')
				return (redi_heredoc(cmd));
			return (redi_input(cmd));
		}
		else if (cmd->str[i] == '>')
		{
			if (cmd->str[i + 1] == '>')
				return (redi_append(cmd));
			return (redi_output(cmd));
		}
	}
}
