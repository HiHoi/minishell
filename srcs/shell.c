/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:09:03 by hoslim            #+#    #+#             */
/*   Updated: 2023/02/05 15:10:32 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	hs_excute_tree(t_cmd *cmd, char ***envp)
{
	if (cmd->type == T_PIPE)
		hs_pipeline(cmd, envp);
	else
		hs_cmd(cmd, envp);
}

int	hs_check_heredoc(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<')
		{
			if (str[i + 1] == '<')
				return (i + 1);
		}
		i++;
	}
	return (0);
}

void	hs_search_tree(t_cmd *cmd, char ***envp)
{
	pid_t	pid;

	if (cmd->exec_flag == 1)
		return ;
	if (hs_check_heredoc(cmd->str) > 0)
		make_temp(cmd);
	if (cmd->right)
		cmd->right->parent_flag = 1;
	pid = fork();
	if (pid < 0)
		error(NULL, "Failed to fork\n", -1);
	else if (pid == 0)
		hs_excute_tree(cmd, envp);
	exit_get_code(pid);
	unlink(".temp_file");
	if (cmd->type == T_PIPE || cmd->type == T_REDI)
	{
		cmd->left->exec_flag = 1;
		cmd->right->exec_flag = 1;
	}
	if (cmd->left != NULL)
		hs_search_tree(cmd->left, envp);
	if (cmd->right != NULL)
		hs_search_tree(cmd->right, envp);
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

