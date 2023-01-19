/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:49:57 by hoslim            #+#    #+#             */
/*   Updated: 2023/01/19 21:48:07 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handler(int signum)
{
	if (signum == SIGINT)
		printf("minishell$\n");
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

void	print_test(t_info *info)
{
	t_cmd	*cur = info->cmd;

	while (cur)
	{
		printf("cur !  t : %d   s : %s\n", cur->type, cur->str);
		if (cur->left)
			printf("left !  t : %d   s : %s\n", cur->right->type, cur->right->str);
		if (cur->right)
			printf("rigth !  t : %d   s : %s\n", cur->left->type, cur->left->str);
		cur = cur->left;
	}
}

void	start_shell(t_info *info)
{
	char			*buf;
	struct termios	term;

	tcgetattr(0, &term);
	term.c_cflag &= ~(ECHOCTL);
	tcsetattr(0, TCSANOW, &term);
	handle_signal();
	while (1)
	{
		buf = readline("minishell$ ");
		if (!buf)
			exit(-1);
		else if (*buf == '\0')
			free(buf);
		else
		{
			add_history(buf);
			parsing_cmd(info, buf);
			//print_test(info);
			//hs_do_something(info);
			hs_search_tree(info->cmd, info->en);
			free(buf);
			info->cmd->str = NULL;
		}
	}
}
