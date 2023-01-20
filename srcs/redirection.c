/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosunglim <hosunglim@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:24:23 by hoslim            #+#    #+#             */
/*   Updated: 2023/01/20 21:32:51 by hosunglim        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redi_input(t_cmd *cmd)
{
	int		in;

	in = open(cmd->right->str, O_RDONLY, 0644);
	if (in < 0)
		error(NULL, "Failed to open\n");
	dup2(in, STDIN_FILENO);
	close(in);
}

void	redi_output(t_cmd *cmd)
{
	int	out;

	out = open(cmd->right->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (out < 0)
		error(NULL, "Failed to open\n");
	dup2(out, STDOUT_FILENO);
	close(out);
}

void	make_temp(char *str)
{
	int		fd;
	char	*line;

	fd = open(".temp_file", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		error(NULL, "Failed to open file");
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
	in = open(".temp_file", O_RDONLY, 0644);
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
		error(NULL, "Failed to open\n");
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
