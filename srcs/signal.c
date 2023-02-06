/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:49:57 by hoslim            #+#    #+#             */
/*   Updated: 2023/02/06 13:33:23 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	exit_code;

//minishell 많이 키면 컨트롤 c 밀림

void	handler(int signum)
{
	char	*str;

	if (signum == SIGINT)
	{
		str = ft_strdup(rl_line_buffer);
		printf("\033[2K");
		printf("minishell$ ");
		printf("%s", str);
		printf("\n");
		free(str);
		str = NULL;
	}
	if (rl_on_new_line() == -1)
		exit(1);
	rl_replace_line("", 1);
	rl_redisplay();
}

void	handle_signal(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}

void	exec_builtin(t_cmd *cmd, char ***envp)
{
	if (cmd->type == T_WORD)
	{
		if (!ft_strncmp(cmd->str, "export", 6))
			ft_export(cmd, envp);
		else if (!ft_strncmp(cmd->str, "unset", 5))
			ft_unset(cmd, envp);
		else if (!ft_strcmp(cmd->str, "$?"))
			ft_echo(cmd, envp);
		else if (!ft_strncmp(cmd->str, "cd", 2))
			ft_cd(cmd, envp);
		else if (!ft_strncmp(cmd->str, "exit", 4))
			ft_exit(cmd, envp);
		return ;
	}
}
