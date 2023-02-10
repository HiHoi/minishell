/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:09:03 by hoslim            #+#    #+#             */
/*   Updated: 2023/02/10 19:40:57 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	hs_excute_tree(t_cmd *cmd, char ***envp)
{
	if (cmd->type == T_PIPE)
		hs_pipeline(cmd, envp);
	else
		hs_cmd(cmd, envp);
	if (cmd->type == T_REDI)
		cmd->left->exec_flag = 1;
	if (cmd->left && cmd->left->exec_flag != 1)
		hs_excute_tree(cmd->left, envp);
	if (cmd->right && cmd->right->exec_flag != 1)
		hs_excute_tree(cmd->right, envp);
}

int	hs_check_heredoc(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
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

//echo | echo prompt error

void	hs_search_tree(t_cmd *cmd, char ***envp)
{
	pid_t	pid;

	if (hs_check_heredoc(cmd->str) > 0)
		make_temp(cmd);
	handle_parent();
	pid = fork();
	if (pid < 0)
		error(NULL, "Failed to fork\n", -1);
	else if (pid == 0)
		hs_excute_tree(cmd, envp);
	exit_get_code(pid);
}

void	exec_cmd(t_cmd *cmd, char ***envp)
{
	if (check_cmd_exec(cmd, envp) == -1)
	{
		if (exec_builtin(cmd, envp) == 1)
			hs_search_tree(cmd, envp);
	}
}

//cat < a > b => 0
// <a cat > b => X
// cat < a>b => X

void	start_shell(t_info *info)
{
	char			*buf;
	struct termios	term;

	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(0, TCSANOW, &term);
	while (1)
	{
		handle_signal();
		buf = readline("minishell$ ");
		if (!buf)
		{
			free(info);
			exit(0);
		}
		else if (*buf == '\0')
			free(buf);
		else
		{
			add_history(buf);
			parsing_cmd(info, buf);
			// print_test(info);
			exec_cmd(info->cmd, &info->en);
			free_cmd(info->cmd, buf);
		}
	}
}
