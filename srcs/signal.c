/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:49:57 by hoslim            #+#    #+#             */
/*   Updated: 2023/01/27 14:41:25 by hoslim           ###   ########.fr       */
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
			printf("left !  t : %d   s : %s\n", cur->left->type, cur->left->str);
		if (cur->right)
			printf("rigth !  t : %d   s : %s\n", cur->right->type, cur->right->str);
		cur = cur->left;
	}
	cur = info->cmd;
	while (cur)
	{
		printf("cur !  t : %d   s : %s\n", cur->type, cur->str);
		if (cur->left)
			printf("left !  t : %d   s : %s\n", cur->left->type, cur->left->str);
		if (cur->right)
			printf("rigth !  t : %d   s : %s\n", cur->right->type, cur->right->str);
		cur = cur->right;
	}
}

//export cd unset 은 메인 프로세스에서 실행하여 제대로된 값이 들어가게끔
//파이프 실행시가 문제

void	exec_builtin(t_cmd *cmd, char **envp)
{
	if (cmd->type == T_WORD)
	{
		if (!ft_strncmp(cmd->str, "export", 6))
		{
			ft_export(cmd, envp);
			cmd->exec_flag = 1;
		}
		else if (!ft_strncmp(cmd->str, "unset", 5))
		{
			ft_unset(cmd, envp);
			cmd->exec_flag = 1;
		}
		return ;
	}
	if (cmd->left != NULL)
		exec_builtin(cmd->left, envp);
	if (cmd->right != NULL)
		exec_builtin(cmd->right, envp);
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
			// print_test(info);
			exec_builtin(info->cmd, info->en);
			hs_search_tree(info->cmd, info->en);
			free(buf);
			free_cmd(info->cmd);
		}
	}
}
