/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:49:57 by hoslim            #+#    #+#             */
/*   Updated: 2023/02/03 15:14:43 by hoslim           ###   ########.fr       */
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

//export cd unset 은 메인 프로세스에서 실행하여 제대로된 값이 들어가게끔
//파이프 실행시가 문제

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

int	check_cmd_exec(t_cmd *cmd, char ***envp)
{
	char	**cmdline;
	char	*parsed;

	cmdline = hj_split_cmd(cmd->str, *envp);
	parsed = hs_parsing_cmd(envp, cmdline[0]);
	if ((hs_check_builtin(cmd) != 1 && parsed == NULL && cmd->type == T_WORD \
	&& ft_strchr(cmd->str, '/') != 0) || *envp == NULL)
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
	if (parsed != cmdline[0])
		free(parsed);
	free_parse(cmdline);
	if (cmd->left != NULL && cmd->type == T_WORD)
		check_cmd_exec(cmd->left, envp);
	if (cmd->right != NULL && cmd->type == T_WORD)
		check_cmd_exec(cmd->right, envp);
	return (-1);
}
