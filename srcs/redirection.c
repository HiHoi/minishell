/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:24:23 by hoslim            #+#    #+#             */
/*   Updated: 2023/02/13 17:21:31 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redi_input(t_cmd *cmd, char ***envp)
{
	int		in;
	char	*path;
	char	**parse;

	if (cmd->left->right)
		path = ft_strtrim(cmd->left->right->str, " ");
	else
		path = ft_strtrim(cmd->right->str, " ");
	parse = hj_split_cmd(path, *envp);
	in = open(parse[0], O_RDONLY | O_EXCL, 0644);
	if (in < 0)
		error(NULL, path, 1);
	dup2(in, STDIN_FILENO);
	close(in);
	free_parse(parse);
}

void	redi_output(t_cmd *cmd, char ***envp)
{
	int		out;
	char	*path;
	char	**parse;

	path = ft_strtrim(cmd->left->right->str, " ");
	parse = hj_split_cmd(path, *envp);
	out = open(parse[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (out < 0)
		error(NULL, path, 1);
	dup2(out, STDOUT_FILENO);
	close(out);
	free_parse(parse);
}

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

void	redi_append(t_cmd *cmd, char ***envp)
{
	int		out;
	char	*path;
	char	**parse;

	path = ft_strtrim(cmd->left->right->str, " ");
	parse = hj_split_cmd(path, *envp);
	out = open(parse[0], O_RDWR | O_CREAT | O_APPEND, 0644);
	if (out < 0)
		error(NULL, path, 1);
	dup2(out, STDOUT_FILENO);
	close(out);
	free_parse(parse);
}

void	hs_redirect(t_cmd *cmd, char ***envp)
{
	int	i;

	if (count_redi(cmd) == 1)
	{
		i = -1;
		while (cmd->str[++i])
		{
			if (cmd->str[i] == '<')
			{
				if (cmd->str[i + 1] == '<')
					return (redi_heredoc(cmd));
				return (redi_input(cmd, envp));
			}
			else if (cmd->str[i] == '>')
			{
				if (cmd->str[i + 1] == '>')
					return (redi_append(cmd, envp));
				return (redi_output(cmd, envp));
			}
		}
	}
	else
		redi_pipe(cmd, envp);
}
