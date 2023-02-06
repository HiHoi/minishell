/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 20:36:27 by hosunglim         #+#    #+#             */
/*   Updated: 2023/02/06 13:13:37 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	exit_code;

void	print_exit(void)
{
	char	*code;

	code = ft_itoa(exit_code);
	write(2, "minishell: ", 12);
	write(2, code, ft_strlen(code));
	write(2, ": command not found\n", 21);
	exit_code = 127;
}

void	echo_print(char *s, int option)
{
	write(1, s, ft_strlen(s));
	if (option == 0)
		write(1, "\n", 1);
}

void	echo_env(char *str, char ***envp, int option)
{
	int		i;
	char	**parse;
	char	*value;

	if (str[0] == '$' && str[1] == '?')
	{
		print_exit();
		return ;
	}
	if (*envp == NULL)
		return ;
	value = NULL;
	i = 0;
	parse = hj_split_cmd(str, *envp);
	value = ft_strdup(parse[1]);
	echo_print(value, option);
}

char	*echo_parse(char *s, char ***envp)
{
	char	**parse;
	char	*str;

	parse = hj_split_cmd(s, *envp);
	if (parse[1] == NULL)
		return (NULL);
	if (ft_strchr(parse[1], '-') > 0)
		str = ft_strdup(parse[2]);
	else
		str = ft_strdup(parse[1]);
	return (str);
}

//$?는 echo의 옵션
int	ft_echo(t_cmd *cmd, char ***envp)
{
	int		option;
	char	*parse;

	cmd->exec_flag = 1;
	option = 0;
	if (ft_strchr(cmd->str, '-') > 0)
		option = 1;
	parse = echo_parse(cmd->str, envp);
	if (ft_strchr(cmd->str, '$') > 0)
		echo_env(cmd->str, envp, option);
	else if (ft_strcmp(parse, "echo") == 0)
		write(1, "\n", 1);
	else
		echo_print(parse, option);
	return (0);
}
