/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 20:36:27 by hosunglim         #+#    #+#             */
/*   Updated: 2023/02/13 19:09:25 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_code;

void	print_exit(char *str, char ***envp)
{
	char	**code;

	code = hj_split_cmd(str, *envp);
	write(2, "minishell: ", 12);
	write(2, code[0], ft_strlen(code[0]));
	write(2, ": command not found\n", 21);
	g_exit_code = 127;
	free_parse(code);
}

void	echo_print(char *s, int option)
{
	write(1, s, ft_strlen(s));
	if (option == 0)
		write(1, "\n", 1);
	g_exit_code = 0;
}

void	echo_env(char *str, char ***envp, int option)
{
	char	**parse;
	char	*value;

	if (str[0] == '$' && str[1] == '?')
	{
		print_exit(str, envp);
		return ;
	}
	if (*envp == NULL)
		return ;
	value = NULL;
	parse = hj_split_cmd(str, *envp);
	value = ft_strdup(parse[1]);
	echo_print(value, option);
	free_parse(parse);
	free(value);
}

char	*echo_parse(char *s, char ***envp, int option)
{
	int		idx;
	char	**parse;
	char	*str;
	int		dest;

	dest = 0;
	parse = hj_split_cmd(s, *envp);
	if (parse[1] == NULL)
	{
		free_parse(parse);
		return (NULL);
	}
	idx = check_option(parse, &dest);
	if (option == 1)
		str = hj_echo_join(parse, idx);
	else
		str = hj_echo_join(parse, 1);
	return (str);
}

//echo -n -n -n -n asd

int	ft_echo(t_cmd *cmd, char ***envp)
{
	int		option;
	char	**temp;
	char	*parse;

	cmd->exec_flag = 1;
	option = 0;
	temp = hj_split_cmd(cmd->str, *envp);
	check_option(temp, &option);
	parse = echo_parse(cmd->str, envp, option);
	if (ft_strchr(cmd->str, '$') > 0)
		echo_env(cmd->str, envp, option);
	else if (!ft_strncmp(parse, "echo", 4))
		write(1, "\n", 1);
	else
		echo_print(parse, option);
	free(parse);
	free_parse(temp);
	return (g_exit_code);
}
