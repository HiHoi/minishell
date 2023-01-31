/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 20:36:27 by hosunglim         #+#    #+#             */
/*   Updated: 2023/01/30 14:28:00 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	exit_code;

void	print_exit(void)
{
	printf("%d\n", exit_code);
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
	char	**value_parse;
	char	*value;

	if (str[0] == '$' && str[1] == '?')
	{
		print_exit();
		return ;
	}
	value = NULL;
	i = 0;
	parse = ft_split(str, '$');
	while ((*envp)[i])
	{
		if (!ft_strncmp(parse[1], (*envp)[i], ft_strlen(parse[1])))
		{
			value_parse = ft_split((*envp)[i], '=');
			value = ft_strdup(value_parse[1]);
			break ;
		}
		i++;
	}
	echo_print(value, option);
}

char	*echo_parse(char *s)
{
	char	**parse;
	char	*str;

	parse = ft_split(s, ' ');
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

	option = 0;
	if (ft_strchr(cmd->str, '-') > 0)
		option = 1;
	parse = echo_parse(cmd->str);
	if (ft_strchr(cmd->str, '$') > 0)
		echo_env(cmd->str, envp, option);
	else if (ft_strcmp(parse, "echo") == 0)
		write(1, "\n", 1);
	else
		echo_print(parse, option);
	return (0);
}
