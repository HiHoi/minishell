/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:49:57 by hoslim            #+#    #+#             */
/*   Updated: 2023/02/01 17:22:11 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int exit_code;

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

void	exec_builtin(t_cmd *cmd, char ***envp)
{
	if (cmd->type == T_WORD)
	{
		if (!ft_strncmp(cmd->str, "export", 6))
		{
			ft_export(cmd, envp);
			cmd->exec_flag = 1;
		}
		if (!ft_strncmp(cmd->str, "unset", 5))
		{
			ft_unset(cmd, envp);
			cmd->exec_flag = 1;
		}
		else if (!ft_strcmp(cmd->str, "$?"))
		{
			ft_echo(cmd, envp);
			cmd->exec_flag = 1;
		}
		else if (!ft_strncmp(cmd->str, "cd", 2))
		{
			cmd->exec_flag = 1;
			ft_cd(cmd, envp);
		}
		return ;
	}
}

int	check_cmd_exec(t_cmd *cmd, char ***envp)
{
	char	**cmdline;
	char	*parsed;

	cmdline = ft_split(cmd->str, ' ');
	parsed = hs_parsing_cmd(envp, cmdline[0]);
	if (hs_check_builtin(cmd) != 1 && parsed == NULL)
	{
		write(2, "minishell: ", 11);
		if (cmdline[0] != NULL)
			write(2, cmdline[0], ft_strlen(cmdline[0]));
		else
			write(2, "syntax error", 12);
		write(2, ": command not found\n", 20);
		exit_code = 127;
		free_parse(cmdline);
		free(parsed);
		return (exit_code);
	}
	free_parse(cmdline);
	free(parsed);
	if (cmd->left != NULL)
		check_cmd_exec(cmd->left, envp);
	if (cmd->right != NULL)
		check_cmd_exec(cmd->right, envp);
	return (-1);
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
			if (check_cmd_exec(info->cmd, &info->en) == -1)
			{
				exec_builtin(info->cmd, &info->en);
				hs_search_tree(info->cmd, &info->en);
			}
			free_cmd(info->cmd, buf);
		}
	}
}
