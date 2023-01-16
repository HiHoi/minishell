/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 12:57:52 by hoslim            #+#    #+#             */
/*   Updated: 2023/01/11 14:46:53 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>

int	main(void)
{
	int		counter;
	int		status;
	pid_t	pid;
	pid_t	pid_child;

	counter = 0;
	pid = fork();
	switch (pid)
	{
	case -1 :
		printf("Failed to make child\n");
		return (-1);
	case 0 :
		printf("I'm child process. I count to 5!\n");
		while (counter < 6)
		{
			printf("자식 : %d\n", counter++);
			sleep(1);
		}
		return (99);
	default:
		printf("I'm parent. I must wait for my child\n");
		pid_child = wait(&status);
		printf("Ended child is %d", pid_child);
		if ((status & 0xff) == 0)
			printf("Normally end. The return is %d\n", status >> 8);
		else
			printf("Adnormally end. The end signal is %d\n", status);
		printf("The End\n");
		while (1)
		{
			printf("parent : %d\n", counter++);
			sleep(1);
		}
	}
}
