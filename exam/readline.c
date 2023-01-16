/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:18:42 by hoslim            #+#    #+#             */
/*   Updated: 2023/01/11 12:54:25 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>
#include <unistd.h>

//rl_on_new_line가 rl_redisplay라는 함수에 커서가 개행 문자를 통해 다음 줄로 이동했음을 알려줄 때 이용되는 함수
//알리미 역할로 별도의 기능은 없음

//rl_replace_line은 rl_line_buffer라는 변수를 이용
//rl_line_buffer는 입력한 문자열을 별도로 유지

void	handler(int signum)
{
	if (signum != SIGINT)
		return ;
	write(1, "\n", 1);
	if (rl_on_new_line() == -1)
		exit(1);
	rl_replace_line("", 1);
	rl_redisplay();
}

int	main(void)
{
	char	*str;

	signal(SIGINT, handler);
	while (1)
	{
		str = readline("Say what? :");
		if (strcmp(str, "exit") == 0)
		{
			printf("exit...\n");
			break ;
		}
		else
			printf("You said :%s\n", str);
		add_history(str);
		free(str);
	}
	return (0);
}
