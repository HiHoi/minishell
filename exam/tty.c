/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 21:17:51 by hoslim            #+#    #+#             */
/*   Updated: 2023/01/12 12:18:07 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>

int	main(void)
{
	int	fd;

	printf("Your tty name is : %s\n", ttyname(0));
	printf("This is an usable process : %d\n", ttyslot());
	printf("%d\n", isatty(0));
	fd = open("./signal.c", O_RDWR);
	printf("%d\n", isatty(fd));
	close(fd);
	fd = open("/dev/ttyS0", O_RDONLY);
	if (fd < -1)
	{
		printf("open error\n");
		return (0);
	}
	printf("%d\n", isatty(fd));
	close(fd);
	return (0);
}
