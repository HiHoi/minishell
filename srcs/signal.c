/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:49:57 by hoslim            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/01/16 18:35:28 by hoslim           ###   ########.fr       */
=======
/*   Updated: 2023/02/12 15:20:13 by hoslim           ###   ########.fr       */
>>>>>>> hoslim
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_exit_code;

void	handler(int signum)
{
	rl_replace_line("", 1);
	if (signum == SIGINT)
<<<<<<< HEAD
		printf("minishell$\n");
	if (rl_on_new_line() == -1)
		exit(1);
	rl_redisplay();
=======
		print_prompt();
>>>>>>> hoslim
}

void	signal_child(int signum)
{
	if (signum == SIGINT)
		printf("^C\n");
	if (signum == SIGQUIT)
		printf("Quit :3\n");
	exit(1);
}

void	handle_child(void)
{
	signal(SIGINT, signal_child);
	signal(SIGQUIT, signal_child);
}

void	handle_parent(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_signal(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}
