/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigaddset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:03:04 by hoslim            #+#    #+#             */
/*   Updated: 2023/01/11 16:08:11 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>

int	main(void)
{
	sigset_t	set;

	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	switch (sigismember(&set, SIGINT))
	{
	case 1:
		printf("SIGINT is admitted.\n");
		break;
	case 0:
		printf("SIGINT is not admitted.\n");
		break;
	default:
		printf("Failed to call sigismember.\n");
	}
	switch (sigismember(&set, SIGSYS))
	{
	case 1:
		printf("SIGSYS is admitted.\n");
		break;
	case 0:
		printf("SIGSYS is not admitted.\n");
		break;
	default:
		printf("Failed to call sigismember");
	}
	return (0);
}
