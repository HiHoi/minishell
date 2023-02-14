/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 12:46:02 by hoslim            #+#    #+#             */
/*   Updated: 2023/02/14 13:14:05 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_exit_code;

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

	if (str && hj_envp_name_chk(str) == 0)
		ret = 0;
	else
		ret = 2;
	return (ret);
}

void	free_fd(int **fd, int count)
{
	int	idx;

	idx = 0;
	while (++idx < count)
		free(fd[idx]);
	free(fd);
}

void	hs_parse_pipe(t_cmd *cmd, char *buf, int i)
{
	char	*left_str;
	char	*right_str;

	cmd->left = init_cmd();
	cmd->right = init_cmd();
	left_str = ft_substr(buf, 0, i);
	right_str = ft_substr(buf, i + 1, ft_strlen(buf) - i);
	cmd->left->str = ft_strdup(left_str);
	cmd->right->str = ft_strdup(right_str);
	free(left_str);
	free(right_str);
}

void	print_prompt(void)
{
	rl_on_new_line();
	rl_redisplay();
	printf("	\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_code = 1;
}
