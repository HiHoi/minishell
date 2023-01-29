/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosunglim <hosunglim@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 20:36:33 by hoslim            #+#    #+#             */
/*   Updated: 2023/01/29 18:42:41 by hosunglim        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//0. check cmd
//1. parsing
//2. built-in
//3. check a cmd with path
//4. check a cmd without path
//5. tokenize
//6. re-asembled token
//7. exec

extern int	exit_code;
//사용시 한번씩 초기화 필요

int	main(int ac, char **av, char **envp)
{
	t_info	*info;

	(void)ac;
	(void)av;
	info = init_info(envp);
	if (!info)
		return (error(NULL, "Failed to initailzie\n"));
	start_shell(info);
	return (0);
}
