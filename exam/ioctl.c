/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ioctl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:19:16 by hoslim            #+#    #+#             */
/*   Updated: 2023/01/12 12:29:41 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	int		fd;
	char	buf[256];

	fd = open("/dev/zero", O_RDWR);
	ioctl(fd, 0, buf);
	printf("buf : %s\n", buf);
	close(fd);
	return (0);
}
