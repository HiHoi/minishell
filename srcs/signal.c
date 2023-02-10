/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:49:57 by hoslim            #+#    #+#             */
/*   Updated: 2023/02/10 18:11:58 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_exit_code;

//cat 상태에서 sigquit 흔적 생김
/*

			str = ft_strdup(rl_line_buffer);
			printf("\033[2K");
			printf("minishell$ ");
			printf("%s", str);
			printf("\n");
			free(str);
			str = NULL;
			if (rl_on_new_line() == -1)
				exit(1);
*/

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

void	handler(int signum)
{
	pid_t	pid;

	pid = waitpid(-1, 0, WNOHANG);
	if (signum == SIGINT)
	{
		if (pid < 0)
			print_prompt();
		else
			printf("^C\n");
	}
	else if (signum == SIGQUIT)
	{
		if (pid < 0)
		{
			rl_on_new_line();
			rl_redisplay();
			printf("  \b\b");
		}
		else
			printf("Quit: 3\n");
	}
}

void	handle_parent(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_signal(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
}
