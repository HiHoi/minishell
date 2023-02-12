/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:49:57 by hoslim            #+#    #+#             */
/*   Updated: 2023/02/12 15:20:13 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_exit_code;

void	handler(int signum)
{
	if (signum == SIGINT)
		print_prompt();
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
