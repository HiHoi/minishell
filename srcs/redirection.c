/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:24:23 by hoslim            #+#    #+#             */
/*   Updated: 2023/01/17 19:56:38 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redi_input(t_cmd *cmd)
{
	int		in;

	in = open(cmd->right->str, O_RDONLY, 0644);
	if (in < 0)
		hs_error_return(NULL, NULL, "Failed to open\n");
	dup2(in, STDIN_FILENO);
	close(in);
}

void	redi_output(t_cmd *cmd)
{
	int	out;

	out = open(cmd->right->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (out < 0)
		hs_error_return(NULL, NULL, "Failed to open\n");
	dup2(out, STDOUT_FILENO);
	close(out);
}

void	make_temp(char *str)
{
	int		fd;
	char	*line;

	fd = open(".temp_file", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		hs_error_return(NULL, NULL, "Failed to open file");
	line = ft_strdup("");
	while (1)
	{
		line = readline(">");
		if (!ft_strcmp(line, str))
			break ;
		write(fd, line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(fd);
}

void	redi_heredoc(t_cmd *cmd)
{
	int	in;

	make_temp(cmd->right->str);
	in = open(cmd->right->str, O_RDONLY, 0644);
	if (in < 0)
		hs_error_return(NULL, NULL, "Failed to open\n");
	dup2(in, STDIN_FILENO);
	close(in);
}

void	redi_append(t_cmd *cmd)
{
	int	out;

	out = open(cmd->right->str, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (out < 0)
		hs_error_return(NULL, NULL, "Failed to open\n");
	dup2(out, STDOUT_FILENO);
	close(out);
}

void	hs_redirect(t_cmd *cmd)
{
	if (ft_strncmp(cmd->str, "<", 1))
		redi_input(cmd);
	else if (ft_strncmp(cmd->str, ">>", 2))
		redi_append(cmd);
	else if (ft_strncmp(cmd->str, ">", 1))
		redi_output(cmd);
	else if (ft_strncmp(cmd->str, "<<", 2))
		redi_heredoc(cmd);
}
