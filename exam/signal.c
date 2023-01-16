/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:59:36 by hoslim            #+#    #+#             */
/*   Updated: 2023/01/11 16:02:02 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

struct sigaction act_new;
struct sigaction act_old;

//sa_handler : signum에 대한 동작을 나타내는 함수의 포인터. 기본적으로 기본 동작을 의미하는 SIG_DFL
//sa_sigaction : sa_flags로 SA_SIGINFO를 사용할 때 설정할 수 있음. sa_handler 대신 설정.
//				신호 처리부에 두가지 정보를 담아서 보냄
//sa_mask : 차단할 신호의 집합. sigprocmask를 통해서 특정 신호를 block시킬지 말지를 정함
//sa_flag : 신호 옵션

void	sigint_handler(int signo)
{
	printf("Make sure to exit. Please repeat again.\n");
	sigaction(SIGINT, &act_old, NULL);
}

//act : signum에 대해서 어떤 동작을 취할지에 대한 정보 -> 시그널에 대한 동작을 수정
//oact : 시그널에 대한 동작을 조회

int	main(void)
{
	act_new.sa_handler = sigint_handler;
	sigemptyset(&act_new.sa_mask);
	sigaction(SIGINT, &act_new, &act_old);
	while (1)
	{
		printf("helloworld\n");
		sleep(1);
	}
	return (0);
}
