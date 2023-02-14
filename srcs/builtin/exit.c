/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:31:10 by hosunglim         #+#    #+#             */
/*   Updated: 2023/02/14 13:09:58 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_code;

int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (1);
	else
		return (0);
}

void	exit_get_code(pid_t pid)
{
	int		status;

	while (1)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			g_exit_code = WEXITSTATUS(status);
			break ;
		}
		if (WIFSIGNALED(status))
		{
			if (status == SIGINT)
				printf("^C\n");
			else if (status == SIGQUIT)
				printf("Quit : 3\n");
			g_exit_code = 128 + status;
			break ;
		}
		else
			break ;
	}
	unlink("/tmp/.temp_file");
}

int	set_exit_code(char *str)
{
	int	idx;

	idx = -1;
	if (str[0] == '-')
		idx = 0;
	if (str[idx + 1] == '\0')
	{
		write(2, "minishell: exit: ", 18);
		write(2, str, ft_strlen(str));
		write(2, ": numeric argument required\n", 29);
		return (255);
	}
	while (str[++idx] != '\0')
	{
		if (ft_isdigit(str[idx]) == 0)
		{
			write(2, "minishell: exit: ", 18);
			write(2, str, ft_strlen(str));
			write(2, ": numeric argument required\n", 29);
			return (255);
		}
	}
	g_exit_code = ft_atoi(str);
	return (g_exit_code);
}

int	ft_exit(t_cmd *cmd, char ***envp)
{
	int		en_len;
	char	**parse;

	cmd->exec_flag = 1;
	parse = hj_split_cmd(cmd->str, *envp);
	g_exit_code = 0;
	if (!ft_strncmp(parse[0], "(exit)", 6))
	{
		free_parse(parse);
		g_exit_code = 1;
		return (g_exit_code);
	}
	en_len = count_line(parse);
	if (en_len > 2)
	{
		write(2, "minishell: exit: too many argument\n", 35);
		g_exit_code = 1;
		free_parse(parse);
		return (g_exit_code);
	}
	write(1, "exit\n", 5);
	if (parse[1])
		g_exit_code = set_exit_code(parse[1]);
	free_parse(parse);
	exit(g_exit_code);
}
