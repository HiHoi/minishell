/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:49:57 by hoslim            #+#    #+#             */
/*   Updated: 2023/02/09 21:14:44 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_exit_code;

//cat 상태에서 sigquit 흔적 생김

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

void	signal_pipe(int sig)
{
	if (sig == SIGINT)
		printf("^C\n");
	if (sig == SIGQUIT)
		printf("Quit: 3\n");
	exit(1);
}

void	handle_parent(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_child(pid_t pid)
{
	if (pid == 0)
	{
		signal(SIGINT, signal_pipe);
		signal(SIGQUIT, signal_pipe);
	}
	else
		signal(SIGINT, SIG_IGN);
}

void	handle_signal(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}
