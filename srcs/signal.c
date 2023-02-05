/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:49:57 by hoslim            #+#    #+#             */
/*   Updated: 2023/02/05 15:14:08 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int exit_code;

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

int	syntax_pipe(t_cmd *cmd)
{
	if (cmd->right->str && cmd->left->str)
		return (1);
	if (cmd->right->str && cmd->left->type == T_PIPE && cmd->left->left->str)
		return (1);
	return (-1);
}

int	syntax_redi(t_cmd *cmd)
{
	if (hs_check_heredoc(cmd->str))
		return (1);
	if (cmd->right && cmd->right->str == NULL)
		return (-1);
	return (1);
}

int	check_cmd_syntax(t_cmd *cmd, char ***envp)
{
	int	ret;

	ret = 1;
	if (cmd->type == T_PIPE)
		ret = syntax_pipe(cmd);
	else if (cmd->type == T_REDI)
		ret = syntax_redi(cmd);
	if (cmd->left != NULL && ret == 1)
		ret = check_cmd_syntax(cmd->left, envp);
	if (cmd->right != NULL && ret == 1)
		ret = check_cmd_syntax(cmd->right, envp);
	return (ret);
}

int	check_cmd_exec(t_cmd *cmd, char ***envp)
{
	if (check_cmd_syntax(cmd, envp) == -1)
	{
		write(2, "minishell: ", 12);
		write(2, cmd->str, ft_strlen(cmd->str));
		write(2, ": syntax error\n", 16);
		exit_code = 127;
		return (exit_code);
	}
	return (-1);
}
